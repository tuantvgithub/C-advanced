#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../red_black_tree/jval.h"
#include "../red_black_tree/jrb.h"
#include "constant.h"
#include "function.h"
#include "graph.h"

/* ############ functions to load data from file data.txt ############ */

char** help(int num, int sz)
{
	char** matrix = (char**)malloc(sizeof(char*)*num);
	
	for(int i = 0; i < num; i++) {
		matrix[i] = (char*)malloc(sizeof(char)*sz);
	}
	
	return matrix;
}

void clear_space_at_head_and_tail(char* str)
{
	int i = 0;

	for(; str[i] == ' '; i++);
	strcpy(str, str+i);

	int n = strlen(str) - 1;

	for(; str[n] == ' '; n--);
	str[n+1] = '\0';	

	return;
}

double convert_str_to_num(char* str)
{
	char* ptr;
	return strtod(str, &ptr);
}

void load_data(char* name_file, struct Graph* g)
{	
	char c;
	char bus[100], cost[100];
	FILE* fl = fopen(name_file, "r");	
	
	if(!fl) return;

	int i = 0, j = 0;
		
	while(fscanf(fl, "%s - %s\n", bus, cost) != EOF) {
		char** story = help(100, 180);		
		do {
			c = fgetc(fl);
			if(c != '-' && c != '\n' && c != EOF) story[i][j++] = c;
			else {
				story[i++][j] = '\0';
				j = 0;
			}
		} while(c != '\n' && c != EOF);

		for(int k = 0; k < i - 1; k++) {
			clear_space_at_head_and_tail(story[k]);
			clear_space_at_head_and_tail(story[k+1]);

			int v1 = add_vertex(g, story[k]);
			int v2 = add_vertex(g, story[k+1]);
			add_edge(g, v1, v2, bus, \
					create_weight(convert_str_to_num(cost), BASE_DISTANCE));
		}
		for(; i < 100; i++) free(story[i]);
		i = 0;
	}

	fclose(fl);
	return;
}

/* ############ functions for menu of program ############ */

void enter(char* src, char* des)
{
	printf("điểm đi : ");
	scanf("%[^\n]s", src);
	while(getchar() != '\n');

	printf("điểm đến : ");
	scanf("%[^\n]s", des);
	while(getchar() != '\n');
	
	return;
}

void tim_duong(struct Graph* g)
{
	char src[180], des[180];
	int path[100], len;

	enter(src, des);
	printf("\n");

	shortest_path(g, get_index(g, src), get_index(g, des));

	printf("\n");	

	return;
}

int check(char** output, char* s, int n)
{
	for(int i =  0; i < n; i++) {
		if(!strcmp(output[i], s)) return 1;
	}

	return 0;
}

int a(struct Graph* g, char* point_bus, char** output)
{
	JRB tree, tmp, node;
	
	int i = get_index(g, point_bus);

	node = jrb_find_int(g->edges, i);

	if(!node) {
		return 0;
	}

	int count = 0;
	tree = (JRB)jval_v(node->val);
	jrb_traverse(tmp, tree) {
		JRB ptr = (JRB)jval_v(tmp->val);
		JRB tmp_;
		jrb_traverse(tmp_, ptr) {
			if(!check(output, jval_s(tmp_->key), count)) {
				strcpy(output[count++], jval_s(tmp_->key));
			}
		}
	}

	return count;
}








