#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

struct Graph load_data(char* name_file)
{
	struct Graph G = graph_new();
	FILE* fl = fopen(name_file, "r");
	int vertices = 0, edges = 0, id1, id2, w;
	char ip[20];

	if(!fl) {
		printf("open file is failed.\n"); 
		return G;
	}

	fscanf(fl, "%d", &vertices);
	for(int i = 0; i < vertices; i++) {
		fscanf(fl, "%d %s", &id1, ip);
		graph_add_vertex(G, id1, ip);
	}
	fscanf(fl, "%d", &edges);
	for(int i = 0; i < edges; i++) {
		fscanf(fl, "%d %d %d", &id1, &id2, &w);
		graph_add_edge(G, id1, id2, w);
		graph_add_edge(G, id2, id1, w);
	}

	fclose(fl);	

	return G;
}

void print_list(struct Graph G)
{
	JRB node;
	
	jrb_traverse(node, G.vertices)
		printf("%d %s\n", jval_i(node->key), jval_s(node->val));	

	return;
}

int main(int argc, char** argv)
{
	struct Graph G;

	if(argv[1] && !strcmp(argv[1], "-h")) {
		printf("C-Advanced, HK20192\n");
		return 0;
	}
	if(argv[2] && !strcmp(argv[1], "-v")) {
		G = load_data(argv[2]);		
		print_list(G);
		graph_drop(G);
		return 0;
	}
	if(argv[4] && !strcmp(argv[1], "-w")) {
		G = load_data(argv[2]);
		double dis = graph_get_edge_value(G, atoi(argv[3]), atoi(argv[4]));		
		if(dis == INFINITIVE_VALUE) dis = -1;
		printf("%d\n", (int)dis);
		return 0;
	}

	if(argv[4] && !strcmp(argv[1], "-p")) {
		G = load_data(argv[2]);
		double dis;
		int len = 0, path[100];
		dis = graph_shortest_path(G, atoi(argv[3]), atoi(argv[4]), path, &len, NULL);
		printf("%d\n", (int)dis);
		for(int i = 0; i < len; i++)
			printf("%s\n", graph_get_vertex(G, path[i]));
		return 0;
	}

	if(argv[3] && !strcmp(argv[1], "-n")) {
		G = load_data(argv[2]);
		int output[100];
		int n = graph_indegree(G, atoi(argv[3]), output, NULL);
		printf("%d\n", n);
		for(int i = 0; i < n; i++)
			printf("%d %s\n", output[i], graph_get_vertex(G, output[i]));
		return 0;
	}

	if(argv[2] && !strcmp(argv[1], "-s")) {
		G = load_data(argv[2]);
	
		int vertices[100], count = 0;
		char str_[1000];
		strcpy(str_, "");
		for(int i = 3; i < argc; i++) {
			if(graph_get_vertex(G, atoi(argv[i]))) {
				char s_[20];
				sprintf(s_, "%s %s", argv[i], graph_get_vertex(G, atoi(argv[i])));
				strcat(str_, s_);
				strcat(str_, "\n");
				vertices[count++] = atoi(argv[i]);
			}
		}
		printf("%d\n", count);
		if(count != 0) printf("%s", str_);
		
		int total = 0;
		char str[1000];
		strcpy(str, "");
		for(int i = 0; i < count - 1; i++) {
			for(int j = i + 1; j < count; j++) {
				int n = graph_get_edge_value(G, vertices[i], vertices[j]);
				if(n != INFINITIVE_VALUE) {
					char s[20];
					sprintf(s, "%d %d %d", vertices[i], vertices[j], (int)n);
					strcat(str, s);
					strcat(str, "\n");
					total++;
				}
			}
		}
		printf("%d\n", total);
		if(total != 0) printf("%s", str);
				
		return 0;
	}

	return 0;
}




















