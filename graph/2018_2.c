#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

struct Graph load_file(char* name_file)
{
	FILE* fl = fopen(name_file, "r");
	struct Graph G = graph_new();
	
	if(!fl) {
		printf("open file is failed.\n");
		return G;
	}

	int number_of_vertices, number_of_edges;
	int id1, id2, cost;

	fscanf(fl, "%d\t%d", &number_of_vertices, &number_of_edges);
	while(fscanf(fl, "%d\t%d\t%d", &id1, &id2, &cost) != EOF) {
		char name1[100], name2[100];
		sprintf(name1, "Castle %d", id1);
		sprintf(name2, "Castle %d", id2);

		graph_add_vertex(G, id1, name1);
		graph_add_vertex(G, id2, name2);
		graph_add_edge(G, id1, id2, cost);
		graph_add_edge(G, id2, id1, cost);
	}
	
	fclose(fl);

	return G;
}

void adjacency_list(struct Graph G)
{
	JRB node, tree, iter;

	jrb_traverse(node, G.edges) {
		printf("- %s : ", graph_get_vertex(G, jval_i(node->key)));
		tree = (JRB) jval_v(node->val);
		jrb_traverse(iter, tree) {
			printf("%d ", jval_i(iter->key));
		}
		printf("\n");
	}

	return;
}

int show_1(struct Graph G, int* output)
{
	JRB node, tree, iter;
	int total = 0, ok;

	jrb_traverse(node, G.edges) {
		ok = 1;
		tree = (JRB) jval_v(node->val);
		jrb_traverse(iter, tree) {
			if(jval_d(iter->val) < 50) {
				ok = 0;
				break;
			}
		}
		if(ok) output[total++] = jval_i(node->key);
	}

	return total;
}

int show_2(struct Graph G, int* output)
{
	JRB node;
	int max = -99999, total = 0;
	int tmp[100];

	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);	
		if(max < n)
			max = n;		
	}
	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);
		if(n == max) output[total++] = jval_i(node->key);
	}

	return total;
}

void find_shortest_path(struct Graph G)
{
	int start = 0, end = 0, length = 0;
	int path[100];

	printf("start : ");
	scanf("%d", &start);
	printf("end : ");
	scanf("%d", &end);
	
	double distance = graph_shortest_path(G, start, end, path, &length, NULL);	
	if (distance == INFINITIVE_VALUE)
		printf("ROUTE NOT FOUND\n");
	else {
		printf("shortes path :\n");
		printf("length : %.1lf\n", distance);
		printf("path : ");
		for(int i = 0; i < length; i++)
			printf("%d  ", path[i]);
		printf("\n");
	}

	return;
}

int Tai_toan_dien(double distance)
{
	return distance < 50 ? 0 : 1;
}

void find_shortest_walking_path(struct Graph G)
{	
	int start = 0, end = 0, length = 0;
	int path[100];

	printf("start : ");
	scanf("%d", &start);
	printf("end : ");
	scanf("%d", &end);
	
	double distance = graph_shortest_path(G, start, end, path, &length, Tai_toan_dien);	
	if (distance == INFINITIVE_VALUE)
		printf("ROUTE NOT FOUND\n");
	else {
		printf("shortes path :\n");
		printf("length : %.1lf\n", distance);
		printf("path : ");
		for(int i = 0; i < length; i++)
			printf("%d  ", path[i]);
		printf("\n");
	}

	return;
}

int main(int argc, char** argv)
{
	int event = 0;
	int n = 0, output_1[100] = {0}, output_2[100] = {0};
	struct Graph G = graph_new();	

	do {
		printf("------ MENU ------\n");
		printf("1. load data\n");
		printf("2. adjacency list\n");
		printf("3. show\n");
		printf("4. find shortest path\n");
		printf("5. find shortest path (only walking)\n");
		printf("6. exit\n");
	
		printf("\nyour choice : ");
		scanf("%d", &event);

		switch(event) {
			case 1:
				G = load_file("dothi.txt");
				break;
			case 2:
				printf("\nAdjacency list : \n\n");
				adjacency_list(G);
				break;
			case 3:
				n = show_1(G, output_1);
				for(int i = 0 ; i < n; i++) printf("%d  ", output_1[i]);
				printf("\n");
				n = show_2(G, output_2);
				for(int i = 0 ; i < n; i++) printf("%d  ", output_2[i]);
				printf("\n");
				break;
			case 4:
				find_shortest_path(G);
				break;
			case 5:
				find_shortest_walking_path(G);
				break;
			case 6:
				break;
			default:
				printf("\nenter number from 1 to 6\n");
		}
		printf("\n");
	} while(event != 6);

	return 0;
}
