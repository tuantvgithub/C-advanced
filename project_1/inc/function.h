#ifndef __FUNCTION_H__
#define __FUNCTION_H__

void to_lower_case(char* str);
void del_space(char* str);
int compare(const char* s1, const char* s2);
void load_data();

void create_location(const char* en_word);
int add_to_dict(const char* en_word, const char* vi_word);
int search_word(const char* en_word, char* output);
int delete_word(const char* en_word);

int check_prefix(const char* prefix, const char* str);
int suggest_word(char* prefix, char** output);
void helper(char** arr, int sz, int elem_sz);
void destroy(char** arr, int sz);

#endif /* __FUNCTION_H__ */
