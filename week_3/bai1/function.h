/*
	#
	# name : function.h
	# author : 
	# function : container all necessary things for bai1.c
	# 		functions, contanst, type data
	#
*/

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#define MAX_PHONE_NUMBER 4

struct Entry {
	char* name;
	char* phone;
	int empty;	
};

struct PhoneBook {
	struct Entry entries[MAX_PHONE_NUMBER];
	int total;
};

struct PhoneBook phone_book_init();
int get_index(char* name, struct PhoneBook book); // return empty index in book to story or index of key name in book 
char* get_phone(struct PhoneBook book, char* name);
void add_phone(struct PhoneBook* book, char* name, char* phone);

#endif /* __FUNCTION_H__ */
