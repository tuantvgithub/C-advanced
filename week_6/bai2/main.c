// request : using libfdr library

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "../../red_black_tree/jrb.h"
#include "../../red_black_tree/jval.h"

int main(int argc, char** argv)
{
	Graph g = create_graph();
	char* output[100];	
	int c = 0;

	add_edge(g, "a", "b");
	add_edge(g, "a", "b");
	add_edge(g, "a", "c");
	add_edge(g, "b", "d");
	add_edge(g, "b", "e");

	printf("Print graph...\n");
	print(g);
	printf("size of graph : %d\n", size_of_graph(g));

	printf("adjacent vertices of node 1 :\n");
	c = get_adjacent_vertices(g, "b", output);	
	if(c == 0) {
		printf("No adjacent vertices.\n");
	} else {
		for(int i = 0; i < c; i++) printf("%s  ", output[i]);
		printf("\n");	
	}

	printf("drop graph...\n");
	drop_graph(g);

	printf("Print graph...\n");
	print(g);

	return 0;
}
