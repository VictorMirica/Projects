// SPDX-License-Identifier: BSD-3-Clause

#include "os_threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* === TASK === */

/* Creates a task that thread must execute */
os_task_t *task_create(void *arg, void (*f)(void *))
{
	// TODO
	// Create the task
	os_task_t *task = malloc(sizeof(os_task_t));

	if (task == NULL) {
		perror("malloc");
		exit(1);
	}
	task->argument = arg;
	task->task = f;

	return task;
}

/* Add a new task to threadpool task queue */
void add_task_in_queue(os_threadpool_t *tp, os_task_t *t)
{
	// TODO
	// Create a new node
	os_task_queue_t *node = malloc(sizeof(os_task_queue_t));

	if (node == NULL) {
		perror("malloc");
		exit(1);
	}
	node->task = t;
	node->next = NULL;

	// Add the new node to the queue
	// Use the taskLock to protect the queue
	pthread_mutex_lock(&(tp->taskLock));
	if (tp->tasks == NULL) {
		tp->tasks = node;
	} else {
		os_task_queue_t *aux = tp->tasks;

		while (aux->next != NULL)
			aux = aux->next;
		aux->next = node;
	}
	pthread_mutex_unlock(&(tp->taskLock));
}

/* Get the head of task queue from threadpool */
os_task_t *get_task(os_threadpool_t *tp)
{
	// TODO
	// Use the taskLock to protect the queue
	pthread_mutex_lock(&(tp->taskLock));

	if (tp->tasks != NULL) {
		// Get the task from the head of the queue
		os_task_queue_t *aux = tp->tasks;

		tp->tasks = tp->tasks->next;
		os_task_t *task = aux->task;
		// Free the node
		free(aux);
		pthread_mutex_unlock(&(tp->taskLock));
		return task;
	}

	pthread_mutex_unlock(&(tp->taskLock));
	return NULL;
}

/* === THREAD POOL === */

/* Initialize the new threadpool */
os_threadpool_t *threadpool_create(unsigned int nTasks, unsigned int nThreads)
{
	// TODO
	// Create the threadpool
	os_threadpool_t *tp = malloc(sizeof(os_threadpool_t));

	if (tp == NULL) {
		perror("malloc");
		exit(1);
	}
	tp->should_stop = 0;
	tp->num_threads = nThreads;
	tp->threads = malloc(sizeof(pthread_t) * nThreads);
	if (tp->threads == NULL) {
		perror("malloc");
		exit(1);
	}
	tp->tasks = NULL;
	pthread_mutex_init(&(tp->taskLock), NULL);

	// Create the threads
	for (unsigned int i = 0; i < nThreads; i++)
		pthread_create(&tp->threads[i], NULL, thread_loop_function, (void *)tp);

	return tp;
}

/* Loop function for threads */
void *thread_loop_function(void *args)
{
	// TODO
	os_threadpool_t *tp = (os_threadpool_t *)args;
	// While the threadpool is not stopped or there are tasks in the queue
	while (tp->should_stop == 0 || tp->tasks != NULL) {
		// Get the task from the queue and execute it
		os_task_t *task = get_task(tp);

		if (task != NULL) {
			task->task(task->argument);
			// Free the task
			free(task);
		}
	}

	// Exit the thread
	pthread_exit(NULL);
}

/* Stop the thread pool once a condition is met */
void threadpool_stop(os_threadpool_t *tp, int (*processingIsDone)(os_threadpool_t *))
{
	// TODO
	// Wait for the threads to finish their tasks
	while (processingIsDone(tp) == 0)
		sleep(1);

	// Stop the threads
	tp->should_stop = 1;
	for (int i = 0; i < tp->num_threads; i++) {
		if (pthread_join(tp->threads[i], NULL) != 0) {
			perror("pthread_join");
			exit(1);
		}
	}
	free(tp->threads);

	// Free the queue
	os_task_queue_t *aux = tp->tasks;

	while (aux != NULL) {
		os_task_queue_t *curr = aux;

		aux = aux->next;
		free(curr->task);
		free(curr);
	}

	// Free the threadpool and the taskLock
	free(tp);
	pthread_mutex_destroy(&(tp->taskLock));
}
