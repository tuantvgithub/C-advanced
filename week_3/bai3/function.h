/*
	##########################################################################
	## April 22 2020
	## name : function.h
	## function : declares functions and defines type data for program main
	##########################################################################
*/

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

struct Entry {
	void* key;	
	void* value;
	struct Entry* next;
};

struct SymbleTable {
	struct Entry** entries;
	int total;
	int size;
	int (*hasher)(void*, int);
	struct Entry* (*create_entry)(void*, void*);
	int (*compare_key)(void*, void*);
};

struct SymbleTable create_symble_table(int number_of_entries, 
				int (*hasher)(void*, int),
			struct Entry* (*create_entry)(void*, void*),
				int (*compare_key)(void*, void*));

void free_entry(struct Entry* entry);
void free_all_entries(struct Entry* st);
void free_symble_table(struct SymbleTable* st);
void add_entry(void* key, void* value, struct SymbleTable* st);
struct Entry* get_entry(void* key, struct SymbleTable st);

#endif /* __FUNCTION_H__ */
