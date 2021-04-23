/*
	#
	# name : function.c
	# author : 
	# function : define functions in function.h
	#
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

struct PhoneBook phone_book_init() {
	struct PhoneBook book;
	struct Entry temp;

	temp.name = temp.phone = NULL;
	temp.empty = 1;

	book.total = 0;	
	for(int i = 0; i < MAX_PHONE_NUMBER; i++) {
		book.entries[i] = temp;
	}

	return book;
}

int get_index(char* name, struct PhoneBook book) {
	int index;
	int sum = 0;
	int loop = MAX_PHONE_NUMBER;
	
	if(book.total > MAX_PHONE_NUMBER) {
		return -1;
	}

	for(int i = 0; name[i] != '\0'; i++) {
		sum += name[i];
	}

	index = sum % MAX_PHONE_NUMBER;
	for(int loop = MAX_PHONE_NUMBER; loop > 0 && !book.entries[index].empty; loop--) {
		if(strcmp(book.entries[index].name, name) == 0) {
			break;		
		}
		index = (index + 1 ) % MAX_PHONE_NUMBER;
	}

	return index;
}

char* get_phone(struct PhoneBook book, char* name) {
	int index = get_index(name, book);
	
	return book.entries[index].phone;
}

void add_phone(struct PhoneBook* book, char* name, char* phone) {
	int index;

	index = get_index(name, *book);
	if(index == -1) {
		printf("Phone book is already full\n");
	} else if(!book->entries[index].empty) {
		book->entries[index].phone = (char*)realloc(book->entries[index].phone, sizeof(char) * strlen(phone));
		strcpy(book->entries[index].phone, phone);	
	} else {
		book->entries[index].name = (char*)malloc(sizeof(char) * strlen(name));
		strcpy(book->entries[index].name, name);
		book->entries[index].phone = (char*)malloc(sizeof(char) * strlen(phone));
		strcpy(book->entries[index].phone, phone);

		book->entries[index].empty = 0;
		book->total++;
	}
}




