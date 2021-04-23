/*
	#################################################################
	## April 22 2020							
	## name : main.c									
	## author : ---									
	## request : tao danh ba dien thoai su dung bo nho dong		
	## 										
	## here we using hash table to story data			
	## each entry in hash table is a linked list			
	#################################################################
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function.h"

#define SIZE_DEFAULT 2

int main(int argc, char** argv) {
	struct PhoneBook book = create_phone_book(SIZE_DEFAULT);
	struct Entry* tmp;

	add_phone_number("Tuan", "111", &book);
	add_phone_number("Tam", "222", &book);
	add_phone_number("Tuan", "333", &book);
	add_phone_number("Tu", "444", &book);
	add_phone_number("Long", "555", &book);
	add_phone_number("Tuan", "666", &book);
	add_phone_number("Sang", "888", &book);
	add_phone_number("Sang", "999", &book);
	add_phone_number("Dung", "000", &book);

//	drop_phone_book(&book);

	for(int i = 0; i < SIZE_DEFAULT; i++) {	
		for(tmp = book.entries[i]; tmp != NULL; tmp = tmp->next) {
			printf("%s(%s)->", tmp->name, tmp->phone);
		}
		printf("NULL\n");
	}

//	printf("Number phone of %s : %s\n", "Tuan", get_entry("Tuan", book)->phone);

	return EXIT_SUCCESS;
}
