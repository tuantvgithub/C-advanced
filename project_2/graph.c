#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../red_black_tree/jval.h"
#include "../red_black_tree/jrb.h"
#include "../red_black_tree/dllist.h"
#include "constant.h"
#include "graph.h"

struct Weight* create_weight(double cost, double distance)
{
	struct Weight* w = (struct Weight*)malloc(sizeof(struct Weight));
	
	w->cost = cost;
	w->distance = distance;

	return w;
}

struct Graph create_graph()
{
	struct Graph g;

	g.vertices = make_jrb();
	g.edges = make_jrb();
	g.num = 0;

	return g;	
}

int add_vertex(struct Graph* g, char* v)
{	
	int i = get_index(g, v);

	if(i == -1) {
		jrb_insert_int(g->vertices, g->num++, new_jval_s(v));
		i = g->num - 1;
	}
	
	return i;
}

void add_edge(struct Graph* g, int v1, int v2,
		char* bus, struct Weight* weight)
{
	JRB node, tree, tmp, tmp_;

	node = jrb_find_int(g->edges, v1);
	if(!node) {
		tree = make_jrb();
		jrb_insert_int(g->edges, v1, new_jval_v(tree));	
	} else {
		tree = (JRB)jval_v(node->val);	
	}

	tmp = jrb_find_int(tree, v2);
	if(!tmp) {
		tmp_ = make_jrb();
		jrb_insert_int(tree, v2, new_jval_v(tmp_));	
	} else {
		tmp_ = (JRB)jval_v(tmp->val);	
	}
	
	if(!jrb_find_str(tmp_, bus)) jrb_insert_str(tmp_, strdup(bus), new_jval_v(weight));	

	return;
}

int get_index(struct Graph* g, char* v)
{
	JRB ptr;

	jrb_traverse(ptr, g->vertices)
		if(!strcmp(jval_s(ptr->val), v))
			return jval_i(ptr->key);
	
	return -1;
}

char* get_point_bus(struct Graph* g, int index)
{
	JRB ptr = jrb_find_int(g->vertices, index);
	
	if(ptr) return jval_s(ptr->val);

	return NULL;
}

char* find_bus(struct Graph* g, int v1, int v2)
{
	JRB node, tmp;
	char bus[100];

	if(v1 == -1 || v2 == -1) return NULL;
	
	strcpy(bus, "( ");

	node = 	jrb_find_int(g->edges, v1);
	if(!node) return 0;
	tmp =  jrb_find_int((JRB)jval_v(node->val), v2);
	if(!tmp) return 0;
	 
	JRB tree = (JRB)jval_v(tmp->val);
	JRB ptr;
	jrb_traverse(ptr, tree) {
		strcat(bus, jval_s(ptr->key));
		strcat(bus, " ");
	}

	strcat(bus, ")");

	return strdup(bus);
}

void print_path(int parent[], int i, struct Graph* g)
{
	if(parent[i] == i) { // i is source
		printf("%s ", get_point_bus(g, i));
		return;
	}
	print_path(parent, parent[i], g);
	printf("-%s-> %s ", find_bus(g, parent[i], i), get_point_bus(g, i));

	return;
}

double get_min_distance(struct Graph* g, int v1, int v2)
{
	JRB node, tree, tmp, ptr;
	double min = INFINITE_VALUE;

	node = jrb_find_int(g->edges, v1);
	if(!node) return INFINITE_VALUE;
	tree = jrb_find_int((JRB)jval_v(node->val), v2);
	if(!tree) return INFINITE_VALUE;
	tmp = (JRB)jval_v(tree->val);
	
	jrb_traverse(ptr, tmp) {
		if(min > ((struct Weight*)jval_v(ptr->val))->distance)
			min = ((struct Weight*)jval_v(ptr->val))->distance;
	}

	return min;
}

int out_degree(struct Graph* g, int v, int* output)
{
	JRB tree, node, ptr;
	int count = 0;
	
	node = jrb_find_int(g->edges, v);
	if(!node) return 0;

	tree = (JRB)jval_v(node->val);
	jrb_traverse(ptr, tree) {
		output[count++] = jval_i(ptr->key);
	}

	return count;
}

void shortest_path(struct Graph* g, int src, int des)
{
	double dist[1000]; // dist[i] will hold the shortest distance from src to i
	int parent[1000]; // array to story shortest path tree
	int visited[1000]; // 1 if vertex i is included in shortest path tree
	int i, output[100];

	if(src == -1 || des == -1) {
		printf("no path.");
		return;
	}
	
	for(i = 0; i < 1000; i++) {
		dist[i] = INFINITE_VALUE;
		visited[i] = 0;
	}
	dist[src] = 0;
	parent[src] = src;

	int c = 0;
	while(c < 1000) {
		double min = INFINITE_VALUE;
		int u;
		for(i = 0; i < 1000; i++)
			if(min > dist[i] && !visited[i])
				min = dist[i], u = i;
			
		visited[u] = 1;
		if(u == des) break;

		int n = out_degree(g, u, output);
		for(i = 0; i < n; i++) {
			int v = output[i];
			double w = BASE_DISTANCE;
			if(!visited[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				parent[v] = u;
			}
		}
		c += 1;
	}

	if(c < 1000)
		print_path(parent, des, g);
	else
		printf("no path.");

	return;
}













