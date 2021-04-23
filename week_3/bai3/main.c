/*
	############################################################
	## April 22 2020
	## name : main.c
	## request : create a phone book using symble table
	## here i used hash table
	############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/* --------------------------------------------- */

int str_hasher(void* str, int range) {
	int sum = 0;
	char* s = (char*)str;

	for(int i = 0; s[i] != '\0'; i++) sum += s[i];
	return sum % range;
}

struct Entry* create_phone(void* name, void* phone_number) {
	struct Entry* new_entry = (struct Entry*)malloc(sizeof(struct Entry));
	
	new_entry->key = strdup((char*)name);
	new_entry->value = strdup((char*)phone_number);
	new_entry->next = NULL;
	
	return new_entry;
}

int str_compare(void* str_1, void* str_2) {
	return strcmp((char*)str_1, (char*)str_2);
}

/* --------------------------------------------- */


/* --------------------------------------------- */

#define MAX_ENTRIES 4

void print_entry_with_index(int index, struct SymbleTable phone_book) {
	for(struct Entry* tmp = phone_book.entries[index];
			tmp != NULL; tmp = tmp->next) {
		printf("%s[%s] --> ", (char*)tmp->key, (char*)tmp->value);		
	}
	printf("empty");
}

void print_list_of_phone_book(struct SymbleTable phone_book) {
	for(int i = 0; i < phone_book.total; i++) {
		print_entry_with_index(i, phone_book);
		printf("\n");
	}
}

char* get_phone_number(char* name, struct SymbleTable phone_book) {
	struct Entry* tmp = get_entry(name, phone_book);
	
	if(!tmp) return "null";
	return (char*)tmp->value;
}

void example() {
	struct SymbleTable phone_book;
	char *name = "tuan";
	char *phone = "123";
	struct Entry* entry = create_phone(name, phone);

	phone_book = create_symble_table(MAX_ENTRIES, str_hasher, create_phone, str_compare);	
	add_entry("tuan", "1", &phone_book);
	add_entry("thanh", "2", &phone_book);
	add_entry("tam", "3", &phone_book);
	add_entry("tuan", "4", &phone_book);
	add_entry("tu", "4", &phone_book);
	add_entry("long", "4", &phone_book);	
	print_list_of_phone_book(phone_book);
	printf("Phone number of %s : %s\n", "tuan", get_phone_number("tuan", phone_book));

	printf("\nFree symble table\n");
	free_symble_table(&phone_book);
	print_list_of_phone_book(phone_book);
}

/* --------------------------------------------- */

int main(int argc, char** argv) {
	example();

	return EXIT_SUCCESS;
}
