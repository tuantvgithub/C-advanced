/*	
	###########################################################
	## April 22 2020										
	## name : function.c					
	## author : ---						
	## function : define necessary functions for program	
	###########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

struct Entry* create_entry(const char* name, const char* phone) {
	struct Entry* tmp;

	if(!name || !phone) return NULL;
	
	tmp = (struct Entry*)malloc(sizeof(struct Entry));
	if(tmp) {

		tmp->name = (char*)malloc(sizeof(char) * strlen(name));	
		strcpy(tmp->name, name);
		tmp->phone = (char*)malloc(sizeof(char) * strlen(phone));
		strcpy(tmp->phone, phone);
		tmp->next = NULL;
	}	

	return tmp;
}

struct PhoneBook create_phone_book(int size) {
	struct PhoneBook book;
	
	book.size = size;
	book.total = 0;
	book.entries = (struct Entry**)malloc(sizeof(struct Entry*) * book.size);
	if(book.entries == NULL) {
		allocation_failed(__LINE__ - 2, __FILE__);
	}
	for(int i = 0; i < book.size; i++) {
		book.entries[i] = NULL;		
	} 

	return book;
}

void free_entries(struct Entry* head_entry) {
	if(!head_entry) return;
	
	free_entries(head_entry->next);

	free(head_entry->name);
	free(head_entry->phone);
	free(head_entry);
}

void free_layer(int i, struct PhoneBook* book) {
	free_entries(book->entries[i]);
	book->entries[i] = NULL;
}

void drop_phone_book(struct PhoneBook* book) {
	for(int i = 0; i < book->size; i++) {
		free_layer(i, book);
	}	
}

int hasher(const char* name, int range) {
	int sum = 0;
		
	for(int i = 0; name[i] != '\0'; i++) sum += name[i];

	return sum % range;
}

void add_phone_number(const char* name, const char* phone, struct PhoneBook* book) {
	struct Entry *new_entry, *tmp;
	int index = hasher(name, book->size);
	
	tmp = get_entry(name, *book);
	if(tmp != NULL) { // entry with key [name] is already exists
		tmp->phone = (char*)realloc(tmp->phone, sizeof(char) * strlen(phone));
		strcpy(tmp->phone, phone);
		return;
	}

	new_entry = create_entry(name, phone);
	if(book->entries[index] != NULL){
		new_entry->next = book->entries[index];
	}
	book->entries[index] = new_entry;
	book->total += 1;
}

struct Entry* get_entry(const char* name, struct PhoneBook book) {
	int index = hasher(name, book.size);
	struct Entry* tmp = NULL;
	
	for(tmp = book.entries[index]; tmp != NULL && strcmp(tmp->name, name) != 0; tmp = tmp->next);

	return tmp;
}

void allocation_failed(int line, const char* file) {
	printf("memory allocation failed in file %s at line %d\n", file, line);
}










