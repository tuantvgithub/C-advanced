/*
	# name : jval.c
	# chua cac dinh nghia cua cac ham cho thu vien jval.h
*/

#include <stdlib.h>
#include <string.h>
#include "jval.h"

// Init data 
Jval new_jval_int(int data)
{
	Jval j;
	j.i = data;
	return j;
}

Jval new_jval_long(long data)
{
	Jval j;
	j.l = data;
	return j;
}

Jval new_jval_float(float data)
{
	Jval j;
	j.f = data;
	return j;
}

Jval new_jval_double(double data)
{
	Jval j;
	j.d = data;
	return j;
}

Jval new_jval_char(char data)
{
	Jval j;
	j.c = data;
	return j;
}

Jval new_jval_str(char* data)
{
	Jval j;
	int len = strlen(data);
	j.str = (char*)malloc(sizeof(char) * len);
	strcpy(j.str, data);
	return j;
}

Jval new_jval_void(void* data, int sz)
{
	Jval j;
	j.v = (char*)malloc(sz);
	memcpy(j.v, data, sz);
}

// get data
int jval_int(Jval j)
{
	return j.i;
}

long jval_long(Jval j)
{
	return j.l;
}

float jval_float(Jval j)
{
	return j.f;
}

double jval_double(Jval j)
{
	return j.d;
}

char jval_char(Jval j)
{
	return j.c;
}

char* jval_str(Jval j)
{
	return j.str;
}

void* jval_void(Jval j)
{
	return j.v;
}

// set data
void jval_set_int(Jval* j, int data)
{
	j->i = data;
}

void jval_set_long(Jval* j, long data)
{
	j->l = data;
}

void jval_set_float(Jval* j, float data)
{
	j->f = data;
}

void jval_set_double(Jval* j, double data)
{
	j->d = data;
}

void jval_set_char(Jval* j, char data)
{
	j->c = data;
}

void jval_set_str(Jval* j, char* data)
{
	int len = strlen(data);
	j->str = (char*)realloc(j->str, sizeof(char)*len);
	strcpy(j->str, data);
}

void jval_set_void(Jval* j, void* data, int sz)
{
	j->v = (char*)realloc(j->v, sz);
	memcpy(j->v, data, sz);
}


/* -------- sort --------- */
/*
	# using three-way to sort data
	#
	# need a function to compare data : type_of_data_compare(Jval, Jval)
	# need a function to swap data : type_of_data_swap(Jval*, int i, int j)
	# need a function to create array with each data : int, float, ...
	#
	# example
	# 	need sort a array containes datas type of int
	#	--> need create two functions
	#		int_compare(), int_swap()
*/

void jval_sort(Jval* buf, int start, int end,
		int (*compare)(Jval, Jval), void (*swap)(Jval*, int, int))
{
	Jval pivot;
	int p_left, p_right; // partition left, partition right
	int p_index; // position of partition
	int amount; // amount of numbers has value = pivot	
	
	if(start < end) {
		pivot = buf[end];
		p_index = start;
		amount = 0;
		for(int i = start; i < end; i++) {
			if(compare(buf[i], pivot) < 0) {
				swap(buf, i, p_index++);
			} else if(compare(buf[i], pivot) == 0) {
				swap(buf, i, p_index++);
				swap(buf, p_index - 1, amount + start);
				amount++;			
			}
		}
		swap(buf, p_index, end);
		p_left = p_right = p_index;
		for(int i = start; compare(buf[i], pivot) == 0 && i < p_left; i++) {
			swap(buf, i, --p_left);
		}
		jval_sort(buf, start, p_left - 1, compare, swap);	
		jval_sort(buf, p_right + 1, end, compare, swap);
	}
}

/* ---------- search ---------- */
/*
	# using binary search
	# 
	# automatic sort array
	# so need a function to compare data and a function to swap data
	#
*/

void jval_search(Jval* buf, int sorted, int start, int end,
	Jval value, int* index,
		int (*compare)(Jval, Jval),
	void (*swap)(Jval*, int, int))
{
	// first need to sort array
	if(!sorted) {
		jval_sort(buf, start, end, compare, swap);
	}
	
	// then using search algorith
	// here we using binary search
	*index = binary_search(buf, start, end, value, compare);	
}

int binary_search(Jval* buf, int start, int end,
	 Jval value, int (*compare)(Jval, Jval))
{
	int mid;

	if(start <= end) {
		mid = (start + end) / 2;
		if(compare(buf[mid], value) == 0) {
			return mid;
		} else if(compare(buf[mid], value) > 0) {
			return binary_search(buf, start, mid - 1, 
					value, compare);
		} else {
			return binary_search(buf, mid + 1, end, 
					value, compare);
		}
	}	

	return -1;
}
















