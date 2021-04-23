/*
	# viet lai ham tim kiem, sap xep tong quat
	#
	# su dung Jval
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jval.h"

#define SMALL_NUMBER 10

Jval* int_create_arr(int size)
{	
	Jval *arr = (Jval*)malloc(sizeof(Jval) * size);

	srand(time(NULL));
	for(int i = 0; i < size; i++) {
		arr[i] = new_jval_int(rand() % 10 + 1);
	}
	return arr;
}

int int_compare(Jval a, Jval b)
{
	if(jval_int(a) == jval_int(b))
		return 0;
	return jval_int(a) > jval_int(b) ? 1 : -1;
}

void int_swap(Jval* buf, int i, int j)
{
	int tmp = jval_int(buf[i]);

	jval_set_int(&buf[i], jval_int(buf[j]));
	jval_set_int(&buf[j], tmp);	
}

void jval_sort_example(int size_of_array, int display)
{
	Jval* arr = int_create_arr(size_of_array);
	
	if(display) {
		for(int i = 0; i < size_of_array; i++) {
			printf("%d  ", jval_int(arr[i]));
		}
		printf("\n");
	}

	jval_sort(arr, 0, size_of_array - 1, int_compare, int_swap);

	if(display) {
		for(int i = 0; i < size_of_array; i++) {
			printf("%d  ", jval_int(arr[i]));
		}
		printf("\n");
	}
}

void jval_search_example(int size)
{
	Jval* arr = int_create_arr(size);
	Jval value = new_jval_int(5);	
	int index;
	
	jval_sort(arr, 0, size - 1, int_compare, int_swap);
	for(int i = 0; i < size; i++) {
		printf("%d  ", jval_int(arr[i]));
	}
	
	jval_search(arr, 1, 0, size - 1, value, &index,
			int_compare, 0);
	printf("\n#index of %d : %d\n", jval_int(value), index);

}

int main(int argc, char** argv)
{
//	jval_sort_example(SMALL_NUMBER, 1);
 	jval_search_example(SMALL_NUMBER);
	return EXIT_SUCCESS;
}





