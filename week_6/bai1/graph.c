// April 24 2020
// name : graph.c
// description : define prototies of functions in graph.h

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct Graph create_graph(int row)
{
	struct Graph g;
	int size = row*row;

	g.matrix = (int*)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++) {
		g.matrix[i] = 0;
	}
	g.row = row;

	return g;
}

void add_edge(struct Graph g, int v1, int v2)
{
	g.matrix[v1*g.row + v2] = g.matrix[v2*g.row + v1] = 1;
}

int get_adjacent_vertices(struct Graph g, int vertex, int* output)
{
	int c = 0;
	int start = vertex * g.row;
	int end = start + g.row - 1;

	for(int i = start; i <= end; i++) {
		if(g.matrix[i] == 1) {
			output[c++] = i - start;
		}
	}

	return c;
}

void drop_graph(struct Graph g)
{
	free(g.matrix);
	g.matrix = NULL;
	g.row = 0;
}

void print_graph(struct Graph g)
{
	for(int i = 0; i < g.row; i++) {
		for(int j = 0; j < g.row; j++) {
			printf("%d ", g.matrix[i*g.row + j]);
		}
		printf("\n");
	}
}




