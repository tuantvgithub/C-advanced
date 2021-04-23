/*
	##########################################################################
	## April 22 2020
	## name : function.c
	## function : defines functions for program main
	##########################################################################
*/

#include <stdlib.h>
#include <string.h>
#include "function.h"

struct SymbleTable create_symble_table(int number_of_entries, 
				int (*hasher)(void*, int),
			struct Entry* (*create_entry)(void*, void*),
				int (*compare_key)(void*, void*)) {
	struct SymbleTable res;
	
	res.entries = (struct Entry**) malloc(sizeof(struct Entry*) * number_of_entries);
	
	for(int i = 0; i < number_of_entries; i++)
		res.entries[i] = NULL;
	
	res.total = number_of_entries;
	res.size = 0;
	res.hasher = hasher;
	res.create_entry = create_entry;
	res.compare_key = compare_key;	

	return res;
}

void free_entry(struct Entry* entry) {
	if(!entry) return;
	if(entry->key) free(entry->key);
	if(entry->value) free(entry->value);
	free(entry);
	entry = NULL;
}

void free_all_entries(struct Entry* entry) {
	if(!entry) return;
	free_all_entries(entry->next);
	free_entry(entry);
}

void free_symble_table(struct SymbleTable* st) {
	for(int i = 0; i < st->total; i++) {
		free_all_entries(st->entries[i]);
		st->entries[i] = NULL;
	}
}

void add_entry(void* key, void* value, struct SymbleTable* st) {
	struct Entry* new_entry = st->create_entry(key, value);
	struct Entry *current = NULL, *previous = NULL;
	int index = st->hasher(key, st->total);
	
	if(!st || !new_entry) return;

	current = st->entries[index];
	for(; current && st->compare_key(key, current->key); current = current->next) {
		previous = current;
	}

	if(!current) { // not found
		new_entry->next = st->entries[index];
		st->entries[index] = new_entry;
		st->size += 1;
	} else {
		new_entry->next = current->next;
		free_entry(current);
		if(!previous) st->entries[index] = new_entry;
		else previous->next = new_entry;		
	}
}

struct Entry* get_entry(void* key, struct SymbleTable st) {
	int index = st.hasher(key, st.total);
	struct Entry *result = NULL;

	for(result = st.entries[index]; result && st.compare_key(key, result->key); result = result->next);

	return result;
}



