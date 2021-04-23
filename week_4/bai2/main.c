#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jrb.h"

void insert(JRB root)
{
	Jval j;
	int i;

	printf("enter number : ");
	scanf("%d", &i);
	j = new_jval_i(i);
	root = jrb_insert_int(root, i, j);
}

void display(JRB root)
{
	JRB tmp;

	for(tmp = jrb_first(root); tmp != jrb_nil(root); tmp = jrb_next(tmp))
		printf("%d  ", jval_i(tmp->val));
	printf("\n");
}

void destroy(JRB root)
{
	jrb_free_tree(root);
}

int main(int argc, char** argv)
{
	JRB root = make_jrb();
	int event;
	
	do {
		printf("1. Insert\n2. Display\n3. Destroy\n0. Exit\nYour choice : ");
		scanf("%d", &event);
		switch(event) {
			case 0:
				break;
			case 1:
				insert(root);
				break;
			case 2:
				display(root);
				break;
			case 3:
				destroy(root);
				break;
			default:
				printf("Error\n");
		}
	} while(event != 0);
	
	return EXIT_SUCCESS;
}






