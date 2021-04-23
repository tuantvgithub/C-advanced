// April 24 2020
// name : graph.h
// description : using matrix to representation a graph 

#ifndef __GRAPH_H__
#define __GRAPH_H__

struct Graph {
	int* matrix;
	int row; // = column
};

struct Graph create_graph(int row);
void add_edge(struct Graph g, int v1, int v2);
int get_adjacent_vertices(struct Graph g, int vertex, int* output); // return the number of adjacent vertices
void drop_graph(struct Graph g);
void print_graph(struct Graph g);

#endif /* __GRAPH_H__ */
