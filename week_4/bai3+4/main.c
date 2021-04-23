#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jrb.h"

char* get_name()
{
	char* name = (char*)malloc(sizeof(char));
	
	printf("Name : ");
	while(getchar() != '\n');
	scanf("%[^\n]s", name);
	
	return name;		
}

long get_phone_number()
{
	long phone;
	
	printf("Phone number : ");
	scanf("%ld", &phone);

	return phone;
}

void add_phone(JRB phone_book, char* name, long phone_number)
{
	JRB tmp = NULL;	
	char* key = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	
	strcpy(key, name);
	tmp = jrb_find_str(phone_book, key);
	if(tmp)	jrb_delete_node(tmp);		
	jrb_insert_str(phone_book, key, new_jval_l(phone_number));
}

void delete_phone(JRB phone_book, char* name)
{
	JRB del = NULL;

	del = jrb_find_str(phone_book, name);
	if(del) jrb_delete_node(del);
	else printf("%s is not exitst!\n", name);

	free(name);	
}

void edit_phone(JRB phone_book, char* name)
{
	long new_phone_number;
	JRB tmp = NULL;
	
	tmp = jrb_find_str(phone_book, name);
	if(!tmp) printf("%s is not exitst!\n", name);
	else {
		printf("New phone number : ");
		scanf("%ld", &new_phone_number);
		tmp->val = new_jval_l(new_phone_number);	
	}
	free(name);
}

JRB load_file_phone_book() {
	JRB phone_book = make_jrb();
	FILE* fl = fopen("phone_book.dat", "r");
	char name[30];
	long phone_number;

	if(!fl) return NULL;
	while(fscanf(fl, "%ld %[^\n]s", &phone_number, name) != EOF) {
		add_phone(phone_book, name, phone_number);
	}

	fclose(fl);
	return phone_book;
}

void update_file_phone_book(JRB phone_book)
{
	FILE* fl = fopen("phone_book.dat", "w");
	JRB tmp = NULL;

	if(!fl) return;
	jrb_traverse(tmp, phone_book) {
		fprintf(fl, "%ld %s\n", jval_l(tmp->val), jval_s(tmp->key));
	}	
	
	fclose(fl);	
}


int main(int argc, char** argv)
{
	JRB phone_book = load_file_phone_book();
	JRB node = NULL;
	int event;
	char* name;
	long phone_number;
	
	do {
		printf("0. Display\n"); // bonus
		printf("1. add phone\n");
		printf("2. delete phone\n");
		printf("3. edit phone\n");
		printf("4. exit\n");
		printf("Your choice : ");
		scanf("%d", &event);
		switch(event) {
			case 0:	
				jrb_traverse(node, phone_book)
					printf("%s - %ld\n", jval_s(node->key), jval_l(node->val));	
				break;
			case 1:
				name = get_name();
				phone_number = get_phone_number();
				add_phone(phone_book, name, phone_number);
				break;
			case 2:
				name = get_name();
				delete_phone(phone_book, name);
				break;
			case 3:
				name = get_name();
				edit_phone(phone_book, name);
				break;
			case 4:
				break;
			default:
				printf("Error!\n");
		}
	} while(event != 4);

	update_file_phone_book(phone_book);

	return EXIT_SUCCESS;
}
