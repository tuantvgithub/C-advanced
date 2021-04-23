/**/

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "function.h"
#include "graph.h"
#include "../red_black_tree/jrb.h"
#include "../red_black_tree/jval.h"

int main(int argc, char** argv)
{
	struct Graph g = create_graph();

	if(argc < 1) printf("need data\n");
	load_data(argv[1], &g);

	int n;
	char** output = help(100, 100);

	int event;
	do {
		printf("1. tìm đường\n");
		printf("2. tim xe\n");
		printf("3. thoát\n");
		printf("\nlựa chọn : ");
		scanf("%d", &event);
		while(getchar() != '\n');
		switch(event) {
			case 1:
				tim_duong(&g);
				break;
			case 2:
				n = a(&g, "Cổ Nhuế", output);
				for(int i = 0; i < n; i++) {
					printf("%s\n", output[i]);
				}
				break;
			case 3:
				break;
			default:
				printf("error!!\n");
		}
		printf("\n");
	} while(event != 2);
	
	return 0;
}
