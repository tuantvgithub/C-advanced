#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "../../red_black_tree/jrb.h"

typedef JRB Graph;

Graph create_graph();
void add_vertices(Graph g, char* v);
void add_edge(Graph g, char* v1, char* v2);
int get_adjacent_vertices(Graph g, char* v, char** output);
void drop_graph(Graph g);

void BFS(Graph g, char* start, char* stop, void(*func)(char*)); // breadth-first search
void DFS(Graph g, char* start, char* stop, void(*func)(char*)); // depth-first search

void print(Graph g);
int size_of_graph(Graph g);

#endif /* __GRAPH_H__ */
