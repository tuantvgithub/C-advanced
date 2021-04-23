#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "../../red_black_tree/jrb.h"
#include "../../red_black_tree/jval.h"
#include "../../red_black_tree/dllist.h"

Graph create_graph()
{
	Graph g = make_jrb();
	return g;
}

void add_vertices(Graph g, char* v)
{
	JRB tmp = jrb_find_str(g, v);
		
	if(!g || tmp) return;
	tmp = make_jrb();
	jrb_insert_str(g, v, new_jval_v(tmp));
	
	return;
}

void add_edge(Graph g, char* v1, char* v2)
{
	JRB tmp = NULL;
	JRB p = NULL;
	
	tmp = jrb_find_str(g, v1);
	if(!tmp) {
		tmp = make_jrb();
		jrb_insert_str(g, v1, new_jval_v(tmp));
		jrb_insert_str(tmp, v2, new_jval_i(1));
	} else {
		p = jrb_find_str((JRB)jval_v(tmp->val), v2);
		if(!p)	jrb_insert_str((JRB)jval_v(tmp->val), v2, new_jval_i(1));
	}
	tmp = jrb_find_str(g, v2);
	if(!tmp) {
		tmp = make_jrb();
		jrb_insert_str(g, v2, new_jval_v(tmp));
		jrb_insert_str(tmp, v1, new_jval_i(1));
	} else {
		p = jrb_find_str((JRB)jval_v(tmp->val), v1);
		if(!p)	jrb_insert_str((JRB)jval_v(tmp->val), v1, new_jval_i(1));
	}
}

int get_adjacent_vertices(Graph g, char* v, char** output)
{
	JRB sub_tree = jrb_find_str(g, v);
	JRB tmp = NULL;
	int c = 0;
	
	if(sub_tree) {
		sub_tree = (JRB)jval_v(sub_tree->val);
		jrb_traverse(tmp, sub_tree) {
			output[c++] = jval_s(tmp->key);
		}
	}

	return c;
}

void drop_graph(Graph g)
{
	JRB sub_tree;
	jrb_traverse(sub_tree, g) {
		jrb_free_tree((JRB)jval_v(sub_tree->val));
		jrb_delete_node(sub_tree);
	}
}

void print(Graph g)
{
	JRB sub_tree = NULL;
	JRB ptr = NULL;
	JRB tmp = NULL;

	jrb_traverse(ptr, g) {
		sub_tree = (JRB)jval_v(ptr->val);
		printf("%s : ", jval_s(ptr->key));
		jrb_traverse(tmp, sub_tree) {
			printf("%s  ", jval_s(tmp->key));
		}
		printf("\n");
	}
}

int size_of_graph(Graph g)
{
	JRB ptr = NULL;
	int size = 0;

	jrb_traverse(ptr, g) {
		size += 1;
	}

	return size;
}

void BFS(Graph g, char* start, char* stop, void(*func)(char*)) 
{
	int* visited = (int*)malloc(sizeof(int) * size_of_graph(g));
	
	for(int i = 0; i < size_of_graph(g); i++) {
		visited[i] = 0;
	}

	
}
























