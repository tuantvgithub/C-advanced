/* 
#
# phat trien ham sap xep tong quat dua tren thuat toan three-way trong tuan 1
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SMALL_NUMBER 15
#define LARGE_NUMBER 1000000

void create_arr(int *arr, int total)
{
	srand(time(NULL));
	for(int i = 0; i < total; i++) {
		arr[i] = rand() % 10 + 1;
	}
}

void print_arr(int *arr, int total)
{
	for(int i = 0; i < total; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

int int_compare(void* a, void* b)
{	
	if(*(int*)a == *(int*)b) {
		return 0;
	} else {
		return *(int*)a > *(int*)b ? 1 : -1;
	}
}

void int_swap(void* buf, int sz, int i, int j)
{
	int tmp = *((char*)buf + i*sz);
	*((char*)buf + i*sz) = *((char*)buf + j*sz);
	*((char*)buf + j*sz) = tmp;
}

void sort(void* buf, int sz, int start, int end,
		int (*compare)(void*, void*),
			void (*swap)(void*, int, int, int))
{
	int p_left, p_right, p_index; // partition left and right
	int pivot_index, i;

	if(start < end) {
		pivot_index = end;
		p_index = start;
		int c = 0; 
		for(i = start; i < pivot_index; i++) {
			if(compare((char*)buf + i*sz, (char*)buf + pivot_index*sz) < 0) {
				swap(buf, sz, i, p_index++);
			} else if(compare((char*)buf + i*sz, (char*)buf + pivot_index*sz) == 0){
				swap(buf, sz, i, p_index++);
				swap(buf, sz, p_index - 1, c + start);
				c++;
			}
		}
		swap(buf, sz, p_index, pivot_index);
		p_left = p_right = p_index;
		for(int k = start; compare((char*)buf + p_index*sz, (char*)buf + k*sz) == 0 && k < p_left; k++) {
			swap(buf, sz, k, --p_left);
		}
		sort(buf, sz, start, p_left - 1, compare, swap);
		sort(buf, sz, p_right + 1, end, compare, swap);
	}
}

void example(int size, int display)
{
	int arr[size];
	clock_t end, start;
	double time_use;
	
	create_arr(arr, size);	
	if(display) print_arr(arr, size);

	start = clock();
	sort(arr, sizeof(int), 0, size - 1, int_compare, int_swap);
	end = clock();

	if(display) print_arr(arr, size);

	time_use = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("sort take %f seconds\n", time_use);
}


int main(int argc, char** argv)
{
	example(LARGE_NUMBER, 0);

	return EXIT_SUCCESS;
}









