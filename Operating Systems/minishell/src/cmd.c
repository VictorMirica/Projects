// SPDX-License-Identifier: BSD-3-Clause

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "cmd.h"
#include "utils.h"

#define READ		0
#define WRITE		1


int redirect(simple_command_t *s, int isInternal)
{
	// Input redirection
	if (s->in != NULL) {
		int fd = open(get_word(s->in), O_RDONLY);

		if (fd < 0) {
			close(fd);
			return SHELL_EXIT;
		}

		if (!isInternal) {
			if (dup2(fd, STDIN_FILENO) < 0) {
				close(fd);
				return SHELL_EXIT;
			}
		}

		close(fd);
	}

	int bothRedirections = 0;
	int fd;
	// Error redirection
	if (s->err != NULL) {
		if (s->io_flags == IO_REGULAR)
			fd = open(get_word(s->err), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(get_word(s->err), O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd < 0) {
			close(fd);
			return SHELL_EXIT;
		}
		if (!isInternal) {
			if (dup2(fd, STDERR_FILENO) < 0) {
				close(fd);
				return SHELL_EXIT;
			}
		}

		if (s->out != NULL && strcmp(get_word(s->out), get_word(s->err)) == 0)
			bothRedirections = 1;
		else
			close(fd);
	}

	// Output redirection
	if (s->out != NULL) {
		if (bothRedirections == 0) {
			if (s->io_flags == IO_REGULAR)
				fd = open(get_word(s->out), O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(get_word(s->out), O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd < 0) {
			return SHELL_EXIT;
			close(fd);
		}
		if (!isInternal) {
			if (dup2(fd, STDOUT_FILENO) < 0) {
				close(fd);
				return SHELL_EXIT;
			}
		}
		close(fd);
	}

	return 0;
}

/**
 * Internal change-directory command.
 */
static bool shell_cd(word_t *dir)
{
	/* TODO: Execute cd. */
	if (dir == NULL)
		return false;

	char *arg = get_word(dir);

	if (chdir(arg) == -1) {
		free(arg);
		return false;
	}

	free(arg);
	return true;
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	/* TODO: Execute exit/quit. */
	return SHELL_EXIT; /* TODO: Replace with actual exit code. */
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	/* TODO: Sanity checks. */
	if (s == NULL)
		return SHELL_EXIT;

	/* TODO: If builtin command, execute the command. */
	char *verb = get_word(s->verb);

	if (strcmp(verb, "exit") == 0 || strcmp(verb, "quit") == 0) {
		free(verb);
		return shell_exit();
	}

	if (strcmp(verb, "cd") == 0) {
		redirect(s, 1);
		bool ret = shell_cd(s->params);

		free(verb);
		if (ret)
			return 0;
		return 1;
	}

	free(verb);

	/* TODO: If variable assignment, execute the assignment and return
	 * the exit status.
	 */
	if (s->verb->next_part != NULL) {
		char *var = get_word(s->verb);
		char *value = get_word(s->verb->next_part->next_part);
		char *saveptr;
		char *name = strtok_r(var, "=", &saveptr);

		int ret = setenv(name, value, 1);

		if (ret < 0) {
			free(var);
			free(value);
			return SHELL_EXIT;
		}

		free(var);
		free(value);
		return ret;
	}

	/* TODO: If external command:
	 *   1. Fork new process
	 *     2c. Perform redirections in child
	 *     3c. Load executable in child
	 *   2. Wait for child
	 *   3. Return exit status
	 */
	pid_t pid = fork();

	switch (pid) {
	case -1:
		return SHELL_EXIT;
	case 0:
		// Child
		// Perform redirections
		if (redirect(s, 0) < 0)
			return SHELL_EXIT;

		int argCount;

		execvp(get_word(s->verb), get_argv(s, &argCount));

		fprintf(stderr, "Execution failed for '%s'\n", get_word(s->verb));

		exit(SHELL_EXIT);

	default:
	{
		// Parent
		int status = 0;
		int ret = 0;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);

		return ret;
	}
	}

	return 0; /* TODO: Replace with actual exit status. */
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool run_in_parallel(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	int ret = 0;
	/* TODO: Execute cmd1 and cmd2 simultaneously. */
	pid_t pid1 = fork();

	switch (pid1) {
	case -1:
		return 1;
	case 0:
		// Child
		ret = parse_command(cmd1, level + 1, father);
		exit(ret);
	default:
		// Parent
		break;
	}

	pid_t pid2 = fork();

	switch (pid2) {
	case -1:
		return 1;
	case 0:
		// Child
		ret = parse_command(cmd2, level + 1, father);
		exit(ret);
	default:
		// Parent
		break;
	}

	int status1 = 0;
	int status2 = 0;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	if (WIFEXITED(status1))
		ret = WEXITSTATUS(status1);

	if (WIFEXITED(status2))
		ret = WEXITSTATUS(status2);

	return ret; /* TODO: Replace with actual exit status. */
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2).
 */
static bool run_on_pipe(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	/* TODO: Redirect the output of cmd1 to the input of cmd2. */
	int pipefd[2];
	int ret = 0;

	if (pipe(pipefd) < 0)
		return 1;

	pid_t pid1 = fork();

	switch (pid1) {
	case -1:
		return 1;
	case 0:
		// Child
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) < 0)
			return 1;

		ret = parse_command(cmd1, level + 1, father);
		exit(ret);
	default:
		break;
	}

	pid_t pid2 = fork();

	switch (pid2) {
	case -1:
		return 1;
	case 0:
		// Child
		close(pipefd[WRITE]);
		if (dup2(pipefd[READ], STDIN_FILENO) < 0)
			return 1;

		ret = parse_command(cmd2, level + 1, father);
		exit(ret);
	default:
		// Parent
		break;
	}

	close(pipefd[READ]);
	close(pipefd[WRITE]);

	int status1 = 0;
	int status2 = 0;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	if (WIFEXITED(status1))
		ret = WEXITSTATUS(status1);

	if (WIFEXITED(status2))
		ret = WEXITSTATUS(status2);

	return ret; /* TODO: Replace with actual exit status. */
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father)
{
	/* TODO: sanity checks */
	if (c == NULL)
		return SHELL_EXIT;

	if (c->op == OP_NONE) {
		/* TODO: Execute a simple command. */
		return parse_simple(c->scmd, level, father);
	}

	int ret = 0;

	switch (c->op) {
	case OP_SEQUENTIAL:
		/* TODO: Execute the commands one after the other. */
		ret = parse_command(c->cmd1, level + 1, c);

		if (ret < 0)
			return ret;

		ret = parse_command(c->cmd2, level + 1, c);
		break;

	case OP_PARALLEL:
		/* TODO: Execute the commands simultaneously. */
		ret = run_in_parallel(c->cmd1, c->cmd2, level, c);
		break;

	case OP_CONDITIONAL_NZERO:
		/* TODO: Execute the second command only if the first one
		 * returns non zero.
		 */
		ret = parse_command(c->cmd1, level + 1, c);
		if (ret != 0)
			ret = parse_command(c->cmd2, level + 1, c);

		break;

	case OP_CONDITIONAL_ZERO:
		/* TODO: Execute the second command only if the first one
		 * returns zero.
		 */
		ret = parse_command(c->cmd1, level + 1, c);
		if (ret == 0)
			ret = parse_command(c->cmd2, level + 1, c);

		break;

	case OP_PIPE:
		/* TODO: Redirect the output of the first command to the
		 * input of the second.
		 */
		ret = run_on_pipe(c->cmd1, c->cmd2, level, c);
		break;

	default:
		return SHELL_EXIT;
	}

	return ret;
}
