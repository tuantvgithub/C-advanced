#include <stdlib.h>
#include "gtk/gtk.h"
#include "./inc/function.h"
#include "./inc/graphic.h"
#include "./inc/constant.h"

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	
	if(argc > 1 && strcmp(argv[1], "history-show") == 0) {
		system("cat ./output/search_history.txt");
		return EXIT_SUCCESS;
	}
	if(argc > 1 && strcmp(argv[1], "history-del") == 0) {
		system("rm ./output/search_history.txt");
		system("touch ./output/search_history.txt");
		return EXIT_SUCCESS;
	}
	if(argc > 1 && strcmp(argv[1], "load") == 0) load_data();	

	main_window();
	gtk_main();

	return EXIT_SUCCESS;
}


















