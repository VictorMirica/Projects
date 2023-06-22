// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "os_graph.h"
#include "os_threadpool.h"
#include "os_list.h"

#define MAX_TASK 100
#define MAX_THREAD 4

int sum;
os_graph_t *graph;
// Using a global variable for the threadpool
os_threadpool_t *tp;

// The function that each thread will execute
void processNode(void *nodeIdxAdr)
{
	// Using the taskLock to protect 'sum'
	pthread_mutex_lock(&(tp->taskLock));
	int nodeIdx = *(int *)nodeIdxAdr;
	os_node_t *node = graph->nodes[nodeIdx];

	sum += node->nodeInfo;
	pthread_mutex_unlock(&(tp->taskLock));

	for (int i = 0; i < node->cNeighbours; i++) {
		// Using the taskLock to protect the visited array
		pthread_mutex_lock(&(tp->taskLock));
		if (graph->visited[node->neighbours[i]] == 0) {
			graph->visited[node->neighbours[i]] = 1;
			pthread_mutex_unlock(&(tp->taskLock));

			// Allocate memory for the node index (the thread's function's argument)
			int *iAdr = (int *)malloc(sizeof(int));

			if (iAdr == NULL) {
				perror("malloc");
				exit(1);
			}
			*iAdr = node->neighbours[i];
			os_task_t *task = task_create((void *)iAdr, processNode);

			add_task_in_queue(tp, task);
		} else {
			pthread_mutex_unlock(&(tp->taskLock));
		}
	}
	// Free the memory allocated for the node index
	free(nodeIdxAdr);
}

// Traverse the graph and add tasks to the threadpool
void traverse_graph(os_threadpool_t *tp)
{
	for (int i = 0; i < graph->nCount; i++) {
		// Using the taskLock to protect the visited array
		pthread_mutex_lock(&(tp->taskLock));
		if (graph->visited[i] == 0) {
			graph->visited[i] = 1;
			pthread_mutex_unlock(&(tp->taskLock));

			// Allocate memory for the node index (the thread's function's argument)
			int *iAdr = (int *)malloc(sizeof(int));

			if (iAdr == NULL) {
				perror("malloc");
				exit(1);
			}
			*iAdr = i;
			// Create a new task and add it to the queue
			os_task_t *task = task_create((void *)iAdr, processNode);

			add_task_in_queue(tp, task);
		} else {
			pthread_mutex_unlock(&(tp->taskLock));
		}
	}
}

// Returns 1 if all nodes have been visited, 0 otherwise
// This function is used to check if the threadpool should stop
int processingIsDone(os_threadpool_t *tp)
{
	int ret = 1;

	for (int i = 0; i < graph->nCount; i++) {
		if (graph->visited[i] == 0) {
			ret = 0;
			break;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s input_file\n", __func__);
		exit(1);
	}

	FILE *input_file = fopen(argv[1], "r");

	if (input_file == NULL) {
		printf("[Error] Can't open file\n");
		return -1;
	}

	graph = create_graph_from_file(input_file);
	if (graph == NULL) {
		printf("[Error] Can't read the graph from file\n");
		return -1;
	}

	// TODO: create thread pool and traverse the graf
	sum = 0;

	tp = threadpool_create(MAX_TASK, MAX_THREAD);

	traverse_graph(tp);

	threadpool_stop(tp, processingIsDone);

	printf("%d", sum);
	return 0;
}
