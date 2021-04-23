#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "graph.h"

char** help(int num, int sz);
double convert_str_to_num(char* str);
void clear_space_at_head_and_tail(char* str);
void load_data(char* name_file, struct Graph* g);

/* ------------ for menu ------------ */

void enter(char* src, char* des); // enter destiation and source
void tim_duong(struct Graph* g);

int check(char** output, char* s, int n);
int a(struct Graph* g, char* point_bus, char** output);

#endif /* __FUNCTION_H__ */
