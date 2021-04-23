/*
	# tao 1 danh ba dien thoai
	# su dung mang
	# co cac chuc nang : them, tim kiem sdt
	# 
	# y tuong giong bang bam
	#
*/

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char** argv) {
	struct PhoneBook book = phone_book_init();

	printf("add Tuan - 123456\n");
	add_phone(&book, "Tuan", "123456");
	printf("add Tam - 652839\n");
	add_phone(&book, "Tam", "652839");
	printf("add Thanh - 123456\n");
	add_phone(&book, "Thanh", "123456");
	printf("add Thanh - 111111\n");
	add_phone(&book, "Thanh", "111111");
	printf("add A - 123456\n");
	add_phone(&book, "A", "123456");
	printf("add B - 123456\n");
	add_phone(&book, "B", "123456");	

	printf("phone of %s : %s\n", "Thanh", get_phone(book, "Thanh"));
	printf("Total : %d\n", book.total);

	return EXIT_SUCCESS;
}

