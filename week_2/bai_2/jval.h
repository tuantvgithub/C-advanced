/*
	# name : jval.h
	# dinh nghia kieu du lieu tong quat Jval
	# khai bao cua 1 so ham cho Jval
*/

#ifndef __JVAL_H__
#define __JVAL_H__

typedef union {
	int i;
	long l;
	float f;
	double d;
	char c;	
	char* str;
	void* v;
} Jval;

/* init data */
Jval new_jval_int(int data);
Jval new_jval_long(long data);
Jval new_jval_float(float data);
Jval new_jval_double(double data);
Jval new_jval_char(char data);
Jval new_jval_str(char* data);
Jval new_jval_void(void* data, int sz);

/* get data */
int jval_int(Jval j);
long jval_long(Jval j);
float jval_float(Jval j);
double jval_double(Jval j);
char jval_char(Jval j);
char* jval_str(Jval j);
void* jval_void(Jval j);

/* set data */
void jval_set_int(Jval* j, int data);
void jval_set_long(Jval* j, long data);
void jval_set_float(Jval* j, float data);
void jval_set_double(Jval* j, double data);
void jval_set_char(Jval* j, char data);
void jval_set_str(Jval* j, char* data);
void jval_set_void(Jval* j, void* data, int sz);

/* ----------- sort ------------ */
/*
	# using three-way algorith
	#	
	# explaintion about parameters
	#	buf _ vung chua du lieu
	#	start _ first index
	#	end _ end index
	#	compare _ function pointer use to compare two data in buf
	#	swap _ function pointer use to swap data in buf
	#
*/
void jval_sort (
	Jval* buf,
	int start,
	int end,
	int (*compare)(Jval, Jval),
	void (*swap)(Jval*, int, int)
);

/* ---------- search ---------- */
/*
	# using binary search algorith
	#
	# explaintion about parameters
	#	buf _ vung chua du lieu
	#	sorted _ as boolean : 1 if array sorted | 0 else
	#	start _ first index
	#	end _ end index
	#	value _ value need to search
	#	index _ pointer type int, index of the value in buf
	#		index = -1 if value is not exists
	#	compare, swap _ same above
	#
*/
void jval_search (
	Jval* buf,
	int sorted,
	int start,
	int end,
	Jval value,
	int* index,
	int (*compare)(Jval, Jval),
	void (*swap)(Jval*, int, int)
);

int binary_search (
	Jval* buf,
	int start,
	int end,
	Jval value,
	int (*compare)(Jval, Jval)
);

#endif /* __JVAL_H__ */





