#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bai2/graph.h"

char** help_me()
{
	char** matrix = (char**)malloc(sizeof(char*)*10);
		
	for(int i = 0; i < 20; i++) {
		matrix[i] = (char*)malloc(sizeof(char*)*10);
	} 
	
	return matrix;
}

Graph load_file()
{
	FILE* fl = fopen("STATIONS", "r");
	Graph g = create_graph();
	char* station = NULL;
	char** stations = NULL;
	char spam[10];
	char c;
	int i, j, k;
	
	if(!fl) return NULL;
	
	// [STATIONS] reading...
	fscanf(fl, "%s", spam); // spam = [STATION]
	do {
		c = fgetc(fl);
		if(c == '=') {
			station = (char*)malloc(sizeof(char)*10);			
			fscanf(fl, "%s", station);
			add_vertices(g, station);
		}
	} while(c != '[');

	// [LINE] reading...
	i = j = k = 0;
	stations = help_me();
	fscanf(fl, "%s", spam); // spam = LINE]
	do {
		c = fgetc(fl);
		if(c == '=') {
			while(1) {
				c = fgetc(fl);
				if(c != ' ' && c != '\n') stations[i][j++] = c;
				else {
					stations[i][j] = '\0';
					j = 0; // chuan bi cho viec doc chuoi tiep theo
					i += 1; // so luong chuoi da doc tang them 1
					if(c == '\n') break; 
				}	
			} 
			for(; k < i - 1; k++) {
				add_edge(g, stations[k], stations[k+1]);	
			}
			k = i; // chuyen sang dong tiep theo
		}
	} while(c != EOF); 

	fclose(fl);
	return g;
}

int get_adjacent_stations(Graph g, char* name_station, char** output)
{
	return get_adjacent_vertices(g, name_station, output);
}

int main(int argc, char** argv)
{
	Graph g = load_file();
	char* output[20];
	int count = 0;
	char* station = "D";

	print(g);
	count = get_adjacent_stations(g, station, output);
	if(count == 0)	printf("No adjacent station with %s.\n", station);
	else {
		printf("Adjacent stations with %s : ", station);
		for(int i = 0; i < count; i++)  printf("%s  ", output[i]);	
		printf("\n");
	}

	drop_graph(g);	
	return 0;
}






