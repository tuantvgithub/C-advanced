#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

struct Graph load_file()
{
	struct Graph G = graph_new();
	FILE *page, *connections;
	int n1 = 0, n2 = 0, id = 0;
	char url[250];

	page = fopen("webpages.txt", "r");
	if(!page) return G;
	else {
		fscanf(page, "%d", &n1);
		printf("%d\n", n1);
		for(int i = 0; i < n1; i++) {
			fscanf(page, "%s %d", url, &id);
			printf("%s %d\n", url, id);
			graph_add_vertex(G, id, url);
		}
		fclose(page);
	}

	connections = fopen("pageConnections.txt", "r");
	if(!connections) return G;
	else {
		int tmp[100];
		fscanf(connections, "%d", &n2);
		printf("%d\n", n2);
		for(int i = 0; i < n2; i++) {
			int count = 0;
			while(1) {
				//printf("count = %d\n", count);
				if(fscanf(connections, "%d", &tmp[count++]) != EOF) {
					printf("%d ", tmp[count-1]); 
				} else break;
//				char c = fgetc(connections);
//				printf("%c", c);
//				if(c == '\n' || c == EOF) {
//					printf("count = %d\n", count);
//					for(int j = 0; j < count; j++)
//						printf("%d ", tmp[j]);
						//graph_add_edge(G, tmp[0], tmp[j], 1);	
//					printf("\n");
//					break;
//				}
			}
			printf("\n");
		}
	}

	return G;
}

void print_min_max(struct Graph G)
{
	JRB node;
	int max = -99999, min = 99999, total = 0;
	int tmp[100], output[100];

	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);	
		if(max < n)
			max = n;		
	}
	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);
		if(n == max) output[total++] = jval_i(node->key);
	}
	
	printf("webpage co nhieu lien ket toi nhat :\n");
	for(int i = 0; i < total; i++)
		printf("%s\n", graph_get_vertex(G, output[i]));
	total = 0;

	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);	
		if(min > n)
			min = n;		
	}
	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);
		if(n == min) output[total++] = jval_i(node->key);
	}

	printf("webpage co it lien ket toi nhat :\n");
	for(int i = 0; i < total; i++)
		printf("%s\n", graph_get_vertex(G, output[i]));

	return;
}

int ok(int a, int* c)
{
	for(int i = 0; i < 3; i++)
		if(a >= c[i]) return 0;
	return 1;
}

void page_rank(struct Graph G, int n)
{
	JRB node, tree, iter;
	int tmp[100], i = 0, j = 0;
	int tmp_[100];

	for(int i = 0; i < n; i++) {
		jrb_traverse(node, G.vertices) {
			double rank = 0;
			i = graph_indegree(G, jval_i(node->key), tmp, NULL);
			for(j = 0; j < i; j++) {
				int k = graph_outdegree(G, tmp[j], tmp_, NULL);
				rank += graph_get_edge_value(G, jval_i(node->key), tmp[j]) / k;
			}
			for(j = 0; j < i; j++)
				graph_set_edge_value(G, tmp[j], jval_i(node->key), rank);
		}	
	}
	
	int c[3] = {999, 999, 999};
	int count = 0;
	for(int i = 0; i < 3; i++) {
		double max = -99999;
		jrb_traverse(iter, G.vertices) {
			int n = graph_indegree(G, jval_i(iter->key), tmp, NULL);
			if(n > 0 && max < graph_get_edge_value(G, tmp[0], jval_i(iter->key)) && ok(max, c))
				max = graph_get_edge_value(G, tmp[0], jval_i(iter->key));
		}
		c[count++] = max;
	}

	int stop = 3;

	for(int i = 0; i < count; i++) {
		jrb_traverse(tree, G.vertices) {
			int n = graph_indegree(G, jval_i(tree->key), tmp, NULL);
			if(n > 0 && c[i] == graph_get_edge_value(G, tmp[0], jval_i(tree->key))) {
				printf("%s\n", jval_s(tree->val));
				stop--;
			}
			if(stop <= 0) break;
		}
		if(stop <= 0) break;
	}

	return;
}


void E(struct Graph G)
{
	JRB node, tree, iter;
	int total = 0, tmp[100];

	printf("so page chi co lien ket den : ");
	jrb_traverse(node, G.vertices) {
		int n = graph_outdegree(G, jval_i(node->key), tmp, NULL);
		if(n == 0) total++;
	}
	printf("%d\n", total);
	total = 0;

	printf("so page chi co lien ket di : ");
	jrb_traverse(node, G.vertices) {
		int n = graph_indegree(G, jval_i(node->key), tmp, NULL);
		if(n == 0) total++;
	}
	printf("%d\n", total);

	return;
}

void F(struct Graph G)
{
	int id1 = 0, id2 = 0;
	int path[100], len = 0;

	printf("id1 : ");
	scanf("%d", &id1);
	printf("id2 : ");
	scanf("%d", &id2);

	double w = graph_shortest_path(G, id1, id2, path, &len, NULL);
	printf("khoang cach ngan nhat : ");
	if(w == INFINITIVE_VALUE || w == 0)
		printf("-1\n");
	else {
		printf("%d", len - 1);
	}

	return;
}

int main(int argc, char** argv)
{
	int event = 0;
	struct Graph G;
	
	do {
		printf("1. webpage\n");
		printf("2. \n");
		printf("3. \n");
		printf("4. \n");
		printf("5. \n");
		printf("6. thoat\n");

		printf("\nlua chon cua ban : ");
		scanf("%d", &event);

		switch(event) {
			case 1:
				G = load_file();
			//	printf("\n");
			//	print_min_max(G);
				break;
			case 2:
				printf("top web quan trong nhat sau 1 lan lap: \n");
				page_rank(G, 1);
				break;
			case 3:
				break;
			case 4:
				E(G);
				break;
			case 5:
				F(G);
				break;
			case 6:
				break;
			default:
				printf("nhap 1 - 6\n");
		}
		printf("\n");
	} while(event != 6);
	
	return 0;
}
