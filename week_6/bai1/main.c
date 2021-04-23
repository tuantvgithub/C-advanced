#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char** argv)
{
	int output[100] = {0};
	int i, n;
	struct Graph g = create_graph(4);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);

	print_graph(g);
	
	n = get_adjacent_vertices(g, 1, output);
	if(!n) printf("No adjacent vertices of node 1\n");
	else {
		printf("Adjacent of node 1 : ");
		for(int j = 0; j < n; j++)
			printf("%d ", output[j]);	
		printf("\n");
	}

	drop_graph(g);

	return 0;
}
