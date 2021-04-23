#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

/* --- create functions --- */
// create window
void main_window();
GtkWidget* create_main_window(const gchar* title, gint length, gint width, gint border);

// top is a menu
GtkWidget* create_top(gpointer user_data);
GtkWidget* create_menu_item(const gchar* name, GCallback func, gpointer user_data);

// head is a box which includes search entry, results area
GtkWidget* create_head(gpointer user_data);
GtkWidget* create_result_area();

// body is a box, it includes suggest area and key press
GtkWidget* create_body(gpointer user_data);

// bottom is a statusbar
GtkWidget* create_bottom(gpointer user_data);

/* --- signals emited --- */
// in top
void add_activate(GtkWidget* widget, gpointer user_data);
void delete_activate(GtkWidget* widget, gpointer user_data);

// in head
void search_entry_activate(GtkWidget* widget, gpointer user_data);
gboolean press_key_tab(GtkWidget* widget, GdkEventKey* event, gpointer user_data);

GtkWidget* get_suggest_area(GtkWidget* main_window_body);
void clear_suggest_area(GtkWidget* suggest_area);
void edit_suggest(GtkWidget* suggest_area, char** output, int num);

/* ---- ---- */
enum ElementOfMainWindow {
	TOP,
	HEAD,
	BODY,
	BOTTOM
};

GtkWidget* get_element_from_main_window(GtkWidget* main_window, int id); // id is element of main window

#define MAIN_WINDOW_TOP(main_window) get_element_from_main_window(main_window, TOP)
#define MAIN_WINDOW_HEAD(main_window) get_element_from_main_window(main_window, HEAD)
#define MAIN_WINDOW_BODY(main_window) get_element_from_main_window(main_window, BODY)
#define MAIN_WINDOW_BOTTOM(main_window) get_element_from_main_window(main_window, BOTTOM)

#endif /* __GRAPHIC_H__ */
