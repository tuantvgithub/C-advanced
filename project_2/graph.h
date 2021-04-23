#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "../red_black_tree/jrb.h"

struct Weight {
	double cost;
	double distance;
};

struct Graph {
	int num; // number of vertices
	JRB vertices; // in this case vertex is a bus point
	JRB edges;
};

/* ------------------------------------ Weight of edges --------------------------------- */

struct Weight* create_weight(double cost, double distance);

/* ------------------------------------ for graph functions --------------------------------- */

struct Graph create_graph();

int add_vertex(struct Graph* g, char* v);
void add_edge(struct Graph* g, int v1, int v2,
	char* bus, struct Weight* weight); /* from v1 to v2 */

/* ------------ shortest path ------------ */

int get_index(struct Graph* g, char* v); /* v stands for point bus */
char* get_point_bus(struct Graph* g, int index);

char* find_bus(struct Graph* g, int v1, int v2);
void print_path(int parent[], int i, struct Graph* g);
double get_min_distance(struct Graph* g, int v1, int v2);
int out_degree(struct Graph* g, int v, int* output);
void shortest_path(struct Graph* g, int v1, int v2);

#endif /* __GRAPH_H__ */
