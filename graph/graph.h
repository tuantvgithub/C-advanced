#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

#define INFINITIVE_VALUE 99999
#define G_SUCCESS 1
#define G_FAILTURE -1

struct Graph {
	JRB vertices;
	JRB edges;
};

struct Graph graph_new();
void graph_drop(struct Graph);

int graph_add_vertex(struct Graph, int id, char*);
int graph_add_edge(struct Graph, int v1, int v2, double weight);

// the 'func' function is the check function for distance
int graph_indegree(struct Graph, int v, int* output, int (*func)(double));
int graph_outdegree(struct Graph, int v, int* output, int (*func)(double));

char* graph_get_vertex(struct Graph, int id);
double graph_get_edge_value(struct Graph, int v1, int v2);
void graph_set_edge_value(struct Graph, int v1, int v2, double w);

int graph_is_DAG(struct Graph);
int graph_topo_sort(struct Graph, int* output);
double graph_shortest_path(struct Graph, int src, int des, int* path, int* length, int (*func)(double)); // the 'func' function is the check function for distance

void BFS(struct Graph, int start, int end, void (*func)(struct Graph, int), void* user);
void DFS(struct Graph, int start, int end, void (*func)(struct Graph, int), void* user);

#endif /* __GRAPH_H__ */
