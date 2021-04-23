/*
	#########################################################################
	## April 22 2020								
	## name : function.h							
	## author : ---								
	## function : define types of data, and declare functions for program 	
	###############################3#########################################
*/

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

struct Entry {
	char* name;
	char* phone;
	struct Entry* next;
};

struct Entry* create_entry(const char* name, const char* phone);

struct PhoneBook {
	struct Entry** entries;
	int total;
	int size;
};

struct PhoneBook create_phone_book(int size); // size : number of cells in the table
void add_phone_number(const char* name, const char* phone, struct PhoneBook* book);
struct Entry* get_entry(const char* name, struct PhoneBook book);

void free_entries(struct Entry* head_entry);
void free_layer(int i, struct PhoneBook* book);
void drop_phone_book(struct PhoneBook* book);

int hasher(const char* name, int range);
void allocation_failed(int line, const char* file);

#endif /* __FUNCTION_H__ */





