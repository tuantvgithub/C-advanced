#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../btree/inc/btree.h"
#include "./inc/function.h"
#include "./inc/constant.h"

void to_lower_case(char* str)
{
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] >= 65 && str[i] <= 90) {
			str[i] = str[i] + 32;		
		}
	}

	return;
}

void del_space(char* str)
{	
	char tmp[WORD_SIZE];
	int i, j, k = 0;

	for(i = 0; str[i] == ' ' || str[i] == '\t'; i++);
	for(j = strlen(str) - 1; str[j] == ' ' || str[j] == '\t'; j--);
	for(; i <= j; i++) tmp[k++] = str[i];

	tmp[k] = '\0';
	strcpy(str, tmp);

	return;
}

int compare(const char* s1, const char* s2)
{
	int l1 = strlen(s1), l2 = strlen(s2);

	if(l1 == l2) {
		return strcmp(s1, s2);
	} else return l1 > l2 ? 1 : -1;
}

void load_data()
{
	FILE* base = fopen("./input/base_dict.txt", "r");
	char en_word[WORD_SIZE], vi_word[WORD_SIZE];
	
	if(!base) return;

	while(fscanf(base, "%s %[^\n]s", en_word, vi_word) != EOF) {
		add_to_dict(en_word, vi_word);
	}
	fclose(base);

	return;
}

void create_location(const char* en_word)
{
	char location[100];
	char command[100];
	char len[10];
	
	sprintf(location, "./data/%c", en_word[0]);
	BTA* tmp = btopn(location, 0, 0);
	if(!tmp) {
		// create ./data/first_letter
		tmp = btcrt(location, 0, 0);

		// create ./data/first_letter_/
		sprintf(command, "mkdir %s_/", location);
		system(command);
	}
	
	sprintf(len, "%ld", strlen(en_word));
	strcat(location, "_/");
	strcat(location, len);

	if(btins(tmp, len, location, 100) == 0) {
		// create ./data/first_letter_/length_of_english_word
		BTA* dict = btcrt(location, 0, 0);
		btcls(dict);
	}
	btcls(tmp);

	return;
}

int add_to_dict(const char* en_word, const char* vi_word)
{
	char english[WORD_SIZE], vietnamese[WORD_SIZE];
	char location[100];

	strcpy(english, en_word);
	del_space(english);
	to_lower_case(english);

	strcpy(vietnamese, vi_word);
	del_space(vietnamese);
	to_lower_case(vietnamese);

	if(strlen(english) == 0 || strlen(vietnamese) == 0) return 0;	

	create_location(english);	

	sprintf(location, "./data/%c_/%ld", english[0], strlen(english));
	BTA* tmp = btopn(location, 0, 0);
	int r_size;
	char str[WORD_SIZE];

	if(btsel(tmp, english, str, WORD_SIZE, &r_size) == 0) {
		if(strstr(str, vietnamese) == NULL) {
			strcat(str, "\n");
			strcat(str, vietnamese);
			btupd(tmp, english, str, WORD_SIZE);
		}	
	} else {	
		btins(tmp, english, vietnamese, WORD_SIZE);
	}
	btcls(tmp);

	return 1;
}

int delete_word(const char* en_word)
{
	char english[WORD_SIZE], vi[WORD_SIZE];
	char location[100];
	int res, r_size;
	
	strcpy(english, en_word);
	del_space(english);
	to_lower_case(english);

	if(strlen(english) == 0) return 0;

	sprintf(location, "./data/%c_/%ld", english[0], strlen(english));
	
	BTA* tmp = btopn(location, 0, 0);
	if(tmp && !btsel(tmp, english, vi, WORD_SIZE, &r_size)) {
		btdel(tmp, english);
		res = 1;
	} else {
		res = 0;
	}

	btcls(tmp);

	return res;
}

int search_word(const char* en_word, char* output)
{
	char location[100];
	char english[WORD_SIZE];
	int res;

	if(strlen(en_word) == 0) { // truong hop loi
		return -1;
	}

	strcpy(english, en_word);
	del_space(english);
	to_lower_case(english);
	sprintf(location, "./data/%c_/%ld", english[0], strlen(english));
	
	BTA* tmp = btopn(location, 0, 0);
	int r_size;
	if(tmp && btsel(tmp, english, output, WORD_SIZE, &r_size) == 0) { // truong hop tim thay
		res = 1;
	}else { // truong hop ko thay
		strcpy(output, "null");
		res = 0;
	}

	btcls(tmp);

	FILE* history = fopen("./output/search_history.txt", "a");
	time_t cur_time;

	time(&cur_time);
	if(history) {
		fprintf(history, "%-20s%-35s%-20s\n", en_word, output, ctime(&cur_time));
		fclose(history);
	}	

	return res;
}

int check_prefix(const char* prefix, const char* str)
{
	int n = strlen(prefix), i = 0;
	
	for(; i < n && prefix[i] == str[i]; i++);
	
	return i < n ? 0 : 1;
}

int suggest_word(char* prefix, char** output)
{
	char location[100], len[10];
	char english[WORD_SIZE], vietnamese[WORD_SIZE];
	int count = 0;

	helper(output, 50, WORD_SIZE);	

	del_space(prefix);
	to_lower_case(prefix);
	sprintf(location, "./data/%c", prefix[0]);
	sprintf(len, "%ld", strlen(prefix));

	BTA* tmp = btopn(location, 0, 0);
	if(tmp) {
		int r_size;
		char n[10];

		btsel(tmp, "", location, 100, &r_size);
		while(count < 50 && btseln(tmp, n, location, 100, &r_size) == 0) {
			if(compare(n, len) > 0) {
				BTA* dict = btopn(location, 0, 0);
				btsel(dict, "", vietnamese, WORD_SIZE, &r_size);
				while(count < 50 && btseln(dict, english, vietnamese, WORD_SIZE, &r_size) == 0) {
					if(check_prefix(prefix, english) == 1) {
						strcpy(output[count], english);
						count += 1;
					}
				}
				btcls(dict);
			}
		}
		
	}
	
	btcls(tmp);	

	return count;	
}

void helper(char** arr, int sz, int element_sz)
{	
	for(int i = 0; i < sz; i++)
		arr[i] = (char*)malloc(sizeof(char)*element_sz);

	return;
}

void destroy(char** arr, int sz)
{
	for(int i = 0; i < sz && arr[i]; i++)
		free(arr[i]);
	
	return;
}











