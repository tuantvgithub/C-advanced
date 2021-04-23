#include "graph.h"

struct Graph graph_new()
{
	struct Graph G;
	
	G.vertices = make_jrb();
	G.edges = make_jrb();

	return G;
}

void graph_drop(struct Graph G) 
{
	JRB iter;
	
	if(G.vertices) jrb_free_tree(G.vertices);
	if(G.edges) {
		jrb_traverse(iter, G.edges)
			jrb_free_tree((JRB)jval_v(iter->val));
		jrb_free_tree(G.edges);
	}

	return;
}

int graph_add_vertex(struct Graph G, int id, char* name)
{
	if(jrb_find_int(G.vertices, id))
		return G_FAILTURE;
	jrb_insert_int(G.vertices, id, new_jval_s(strdup(name)));

	return G_SUCCESS;
}

int graph_add_edge(struct Graph G, int v1, int v2, double weight)
{
	JRB node, tree;

	if(graph_get_edge_value(G, v1, v2) != INFINITIVE_VALUE) return G_FAILTURE;

	node = jrb_find_int(G.edges, v1);
	if(node)
		tree = (JRB) jval_v(node->val);
	else {
		tree = make_jrb();
		jrb_insert_int(G.edges, v1, new_jval_v(tree));
	}
	jrb_insert_int(tree, v2, new_jval_d(weight));

	return G_SUCCESS;
}

int graph_indegree(struct Graph G, int v, int* output, int (*func)(double))
{
	JRB node, tree, iter;
	int total = 0;

	jrb_traverse(iter, G.edges) {
		tree = (JRB) jval_v(iter->val);
		node = jrb_find_int(tree, v);
		if(node) {			
			if(func && !func(jval_d(node->val))) continue;
			output[total++] = jval_i(iter->key);
		}
	}

	return total;
}

int graph_outdegree(struct Graph G, int v, int* output, int (*func)(double))
{
	JRB node, tree;
	int total = 0;

	node = jrb_find_int(G.edges, v);
	if(!node)
		return 0;
	tree = (JRB) jval_v(node->val);
	jrb_traverse(node, tree) {
		if(func && !func(jval_d(node->val))) continue;			
		output[total++] = jval_i(node->key);
	}	
	return total;
}

char* graph_get_vertex(struct Graph G, int id)
{
	JRB node = jrb_find_int(G.vertices, id);
	
	return node == NULL ? NULL : jval_s(node->val);
}

double graph_get_edge_value(struct Graph G, int v1, int v2)
{
	if(v1 == v2) return 0;
	JRB node = jrb_find_int(G.edges, v1);
	
	if(node)
		node = jrb_find_int((JRB) jval_v(node->val), v2);
	
	return node == NULL ? INFINITIVE_VALUE : jval_d(node->val);
}

void graph_set_edge_value(struct Graph G, int v1, int v2, double w)
{
	if(v1 == v2) return;
	JRB node = jrb_find_int(G.edges, v1);

	if(node)
		node = jrb_find_int((JRB) jval_v(node->val), v2);

	if(node)
		node->val = new_jval_d(w);

	return;
}

int graph_is_DAG(struct Graph G)
{
	int visited[1000] = {};
	int n, output[100], i, u, v, start;
	Dllist node, stack;
	JRB vertex;

	jrb_traverse(vertex, G.vertices) {
		memset(visited, 0, sizeof(visited));
		start = jval_i(vertex->key);
		stack = new_dllist();
		dll_append(stack, new_jval_i(start));

		while(!dll_empty(stack)) {
			node = dll_last(stack);
			u = jval_i(node->val);
			dll_delete_node(node);
			if(!visited[u]) {
				visited[u] = 1;
				n = graph_outdegree(G, u, output, NULL);
				for(i = 0; i < n; i++) {
					v = output[i];
					if(v == start) // cycle detected
						return 0;
					if(!visited[v])
						dll_append(stack, new_jval_i(v));
				}
			}
		}
	}
	
	return 1; // no cycle
}

int graph_topo_sort(struct Graph G, int* output)
{
	int indeg[1000], tmp[100], m, i, u, v, total;
	JRB vertex;
	Dllist node, queue;
	
	queue = new_dllist();
	jrb_traverse(vertex, G.vertices) {
		u = jval_i(vertex->key);
		indeg[u] = graph_indegree(G, u, tmp, NULL);
		if(indeg[u] == 0)
			dll_append(queue, new_jval_i(u));
	}
	total = 0;
	while(!dll_empty(queue)) {
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);
		output[total++] = u;
		m = graph_outdegree(G, u, tmp, NULL);
		for(i = 0; i < m; i++) {
			v = tmp[i];
			indeg[v]--;
			if(indeg[v] == 0)
				dll_append(queue, new_jval_i(v));
		}
	}

	return total;
}

double graph_shortest_path(struct Graph G, int src, int des, int* path, int* length, int (*func)(double))
{
	int previous[100], visited[100], u;
	double distance[100];
	Dllist queue = new_dllist();
	Dllist iter, node;

	if(src == des) return 0;
	JRB t;
	t = jrb_find_int(G.vertices, src);
	if(!t) return 0;
	t = jrb_find_int(G.vertices, des);
	if(!t) return 0;

	for(int i = 0; i < 100; i++) {
		distance[i] = INFINITIVE_VALUE;
		visited[i] = 0;
	}
	distance[src] = 0;
	visited[src] = 1;
	dll_append(queue, new_jval_i(src));
	
	while(!dll_empty(queue)) {
		double min = INFINITIVE_VALUE;
		dll_traverse(iter, queue) {
			u = jval_i(iter->val);
			if(min > distance[u]) {
				min = distance[u];
				node = iter;
			}	
		}
		u = jval_i(node->val);
		dll_delete_node(node);
		if(u == des) break;

		int n, v, output[100];
		double w;
		n = graph_outdegree(G, u, output, func);
		for(int i = 0; i < n; i++) {
			v = output[i];
//			w = graph_get_edge_value(G, u, v);
			w = 1;	
			if(distance[v] > distance[u] + w) {		
				distance[v] = distance[u] + w;
				previous[v] = u;	
			}
			if(!visited[v]) {
				visited[v] = 1;
				dll_append(queue, new_jval_i(v));			
			}
		}
	}

	int n, tmp[100];
	if(distance[des] != INFINITIVE_VALUE) {
		tmp[0] = des;
		n = 1;
		u = des;
		while(u != src) {
			u = previous[u];
			tmp[n++] = u;
		}

		*length = n;
		for(int i = n - 1; i >= 0; i--)
			path[n-i-1] = tmp[i];
	}

	free_dllist(queue);
	
	return distance[des];
}

void BFS(struct Graph G, int start, int end, void (*func)(struct Graph, int), void* user)
{
	int visited[1000] = {0};
	int n, output[100], i, u, v;
	Dllist node, queue;
	
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	while(!dll_empty(queue)) {
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);
		if(!visited[u]) {
			func(G, u);
			visited[u] = 1;
			if(u == end) return;
			n = graph_indegree(G, u, output, NULL);
			for(i = 0; i < n; i++) {
				v = output[i];
				if(!visited[v])	
					dll_append(queue, new_jval_i(v));
			}
		}
	}

	return;
}

void DFS(struct Graph G, int start, int end, void (*func)(struct Graph, int), void* user)
{
	int visited[1000] = {0};
	int n, output[100], i, u, v;
	Dllist node, stack;
	
	stack = new_dllist();
	dll_append(stack, new_jval_i(start));

	while(!dll_empty(stack)) {
		node = dll_last(stack);
		u = jval_i(node->val);
		dll_delete_node(node);
		if(!visited[u]) {
			func(G, u);
			visited[u] = 1;
			if(u == end) return;
			n = graph_indegree(G, u, output, NULL);
			for(i = 0; i < n; i++) {
				v = output[i];
				if(!visited[v])
					dll_append(stack, new_jval_i(v));
			}
		}
	}

	return;
}



















