/*
   gcc -o main main.c ../red_black_tree/jrb.c ../red_black_tree/dllist.c ../red_black_tree/jval.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../red_black_tree/jrb.h"
#include "../red_black_tree/dllist.h"
#include "../red_black_tree/jval.h"

Dllist find_node(char c, Dllist queue)
{
	Dllist ptr;

	dll_traverse(ptr, queue) {
		if(c == jval_c(jrb_val((JRB)jval_v(dll_val(ptr))))) return ptr;
	}
	
	return NULL;
}

Jval create_data(int tan_suat, char ky_tu, JRB left, JRB right)
{
	JRB value = make_jrb();

//	printf("%c\t%d\n", ky_tu, tan_suat);

	if(!left && !right) {
		value->key = new_jval_i(tan_suat);
		value->val = new_jval_c(ky_tu);		
	} else if(left && right){
		JRB tree = make_jrb();

		left->key = new_jval_i(0);
		right->key = new_jval_i(0);

		jrb_insert_int(tree, 0, new_jval_v(left));
		jrb_insert_int(tree, 1, new_jval_v(right));
		
		value->key = new_jval_i(tan_suat);
		value->val = new_jval_v(tree);
	}
	
	return new_jval_v(value);
}

void add_to_queue(Dllist queue, Jval node)
{
	int tan_suat = jval_i(((JRB)jval_v(node))->key);	
	Dllist tmp;

	dll_traverse(tmp, queue) {
		int i = jval_i(((JRB)jval_v(dll_val(tmp)))->key);
		if(tan_suat < i) break;
	}

	if(!tmp) dll_append(queue, node);
	else dll_insert_b(tmp, node);

	return;
}

void build_sorted_queue(char* str, int index, Dllist queue)
{
	Dllist tmp;
	int tan_suat = 1;

	if(str[index] == '\0') return;
	
	tmp = find_node(str[index], queue);
	if(tmp) {
		tan_suat += jval_i(((JRB)jval_v(dll_val(tmp)))->key);
		dll_delete_node(tmp);
	}

//	printf("input of create_data :\n");
	Jval new_node = create_data(tan_suat, str[index], NULL, NULL);
//	printf("output of create_data :\n");
//	printf("%c\t%d\n", jval_c(((JRB)jval_v(new_node))->val), jval_i(((JRB)jval_v(new_node))->key));	

	add_to_queue(queue, new_node);

	build_sorted_queue(str, index + 1, queue);

	return; 
}

Jval DeQueue(Dllist queue) {
	Dllist tmp = dll_first(queue);
	Jval data = dll_val(tmp);

	dll_delete_node(tmp);

	return data;
}

int dll_len(Dllist queue)
{
	int count = 0;
	Dllist tmp;

	dll_traverse(tmp, queue) count++;

	return count;
}

JRB build_huffman_tree(Dllist queue)
{
	while(dll_len(queue) > 1) {
		Jval first = DeQueue(queue);
		Jval second = DeQueue(queue);

		int tan_suat = jval_i(((JRB)jval_v(first))->key) + jval_i(((JRB)jval_v(second))->key);

		add_to_queue(queue, create_data(tan_suat, '\0', (JRB)jval_v(first), (JRB)jval_v(second)));
	}

	return (JRB)jval_v(DeQueue(queue));	
}
	
int main(int argc, char** argv)
{
	Dllist queue = new_dllist();

	build_sorted_queue("Eerie eyes seen near lake", 0, queue);
	int num = dll_len(queue);
	char code_table[10][10];

//	Dllist tmp;
//	dll_traverse(tmp, queue) {
//		printf("%c\t%d\n", jval_c(((JRB)jval_v(dll_val(tmp)))->val), jval_i(((JRB)jval_v(dll_val(tmp)))->key));
//	}	

	JRB huffman_tree = build_huffman_tree(queue);

	return 0;
}




