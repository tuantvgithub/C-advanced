#include "gtk/gtk.h"
#include "gdk/gdk.h"
#include "./inc/function.h"
#include "./inc/graphic.h"
#include "./inc/constant.h"

void main_window()
{
	GtkWidget* window;
	GtkWidget* window_box;
	GtkWidget *top, *head, *body, *bottom;
	GtkWidget* sep;
	
	window = create_main_window(MAIN_WINDOW_TITLE,
		MAIN_WINDOW_WIDTH,
		MAIN_WINDOW_HIGHT,
		MAIN_WINDOW_BORDER_WIDTH);

	window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), window_box);

	top = create_top(window);
	head = create_head(window);
	body = create_body(NULL);
	bottom = create_bottom(NULL);
	
	gtk_box_pack_start(GTK_BOX(window_box), top, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(window_box), head, FALSE, FALSE, 0);

	sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(window_box), sep, FALSE, FALSE, 6);

	gtk_box_pack_start(GTK_BOX(window_box), body, TRUE, TRUE, 15);
	gtk_box_pack_end(GTK_BOX(window_box), bottom, FALSE, FALSE, 0);

	gtk_widget_show_all(window);

	return;
}

GtkWidget* get_element_from_main_window(GtkWidget* main_window, int id_of_element)
{
	GtkWidget *top, *head, *body, *bottom;
	GList* l = gtk_container_get_children(GTK_CONTAINER(main_window));
	GtkWidget* main_window_box = (GtkWidget*)l->data;

	g_list_free(l);	
	l = gtk_container_get_children(GTK_CONTAINER(main_window_box));
	top = (GtkWidget*)l->data;
	
	l = g_list_next(l);
	head = (GtkWidget*)l->data;

	l = g_list_next(l); // step over separator element

	l = g_list_next(l);
	body = (GtkWidget*)l->data;

	l = g_list_next(l);
	bottom = (GtkWidget*)l->data;

	g_list_free(l);

	switch(id_of_element) {
		case TOP:
			return top;
		case HEAD:
			return head;
		case BODY:
			return body;
		case BOTTOM:
			return bottom;
		default:
			return NULL;
	}
}

/*********************** create window **********************/
GtkWidget* create_main_window(const gchar* title, gint length, gint width, gint border)
{
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), length, width);
	gtk_container_set_border_width(GTK_CONTAINER(window), border);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return window;
}

/********************** create top *************************/
GtkWidget* create_top(gpointer user_data)
{
	GtkWidget* top = gtk_menu_bar_new();
	GtkWidget *menu, *menu_item;

	menu = gtk_menu_new();

	menu_item = create_menu_item("add", (GCallback)add_activate, (GtkWidget*)user_data);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

	menu_item = create_menu_item("delete", (GCallback)delete_activate, (GtkWidget*)user_data);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

	menu_item = create_menu_item("exit", gtk_main_quit, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

	menu_item = create_menu_item(". . .", NULL, NULL);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(top), menu_item);

	return top;
}

GtkWidget* create_menu_item(const gchar* name, GCallback func, gpointer user_data)
{
	GtkWidget* menu_item = gtk_menu_item_new_with_label(name);

	if(func) g_signal_connect(G_OBJECT(menu_item), "activate", G_CALLBACK(func), (gpointer)user_data);

	return menu_item;
}

// signals emits in top
void add_activate(GtkWidget* widget, gpointer user_data)
{
	GtkWidget* add_dialog = gtk_dialog_new_with_buttons("add",
		GTK_WINDOW((GtkWidget*)user_data),
		GTK_DIALOG_MODAL,
		"Ok", GTK_RESPONSE_OK,
		"Cancel", GTK_RESPONSE_CANCEL,
		NULL);

	GtkWidget* en_entry = gtk_entry_new();
	GtkWidget* vi_entry = gtk_entry_new();

	GtkWidget* en_label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(en_label), "<i><small><small>english</small></small></i>");
	GtkWidget* en_frame = gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(en_frame), en_label);
	gtk_container_add(GTK_CONTAINER(en_frame), en_entry);

	GtkWidget* vi_label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(vi_label), "<i><small><small>vietnamese</small></small></i>");
	GtkWidget* vi_frame = gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(vi_frame), vi_label);
	gtk_container_add(GTK_CONTAINER(vi_frame), vi_entry);

	GtkWidget* add_dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(add_dialog_box), en_frame, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(add_dialog_box), vi_frame, FALSE, FALSE, 0);

	GtkWidget* content_area = gtk_dialog_get_content_area(GTK_DIALOG(add_dialog));
	gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);
	gtk_container_add(GTK_CONTAINER(content_area), add_dialog_box);

	gtk_widget_show_all(add_dialog);

	GtkWidget* main_window_bottom = MAIN_WINDOW_BOTTOM((GtkWidget*)user_data);
	guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(main_window_bottom), "");
	const gchar notification[200];	

	const gchar *en_text, *vi_text;
	char english[WORD_SIZE], vietnamese[WORD_SIZE];

	switch(gtk_dialog_run(GTK_DIALOG(add_dialog))) {
		case GTK_RESPONSE_OK:
			en_text = gtk_entry_get_text(GTK_ENTRY(en_entry));
			vi_text = gtk_entry_get_text(GTK_ENTRY(vi_entry));
			strcpy(english, (char*)en_text);
			strcpy(vietnamese, (char*)vi_text);
			
			int result = add_to_dict(english, vietnamese);
			if(result == 0) {
				sprintf((char*)notification, "_: add/%s/%s/failed", english, vietnamese);
			} else {			
				sprintf((char*)notification, "_: add/%s/%s/ok", english, vietnamese);
			}	
			break;
		case GTK_RESPONSE_CANCEL:
		case GTK_RESPONSE_NONE:
		default:
			en_text = gtk_entry_get_text(GTK_ENTRY(en_entry));
			vi_text = gtk_entry_get_text(GTK_ENTRY(vi_entry));
			strcpy(english, (char*)en_text);
			strcpy(vietnamese, (char*)vi_text);

			sprintf((char*)notification, "_: add/%s/%s/cancel", english, vietnamese);	
			break; 
	}

	gtk_statusbar_push(GTK_STATUSBAR(main_window_bottom), id, notification);
	gtk_widget_destroy(add_dialog);	

	return;
}

void delete_activate(GtkWidget* widget, gpointer user_data)
{
	GtkWidget* delete_dialog = gtk_dialog_new_with_buttons("delete",
		GTK_WINDOW((GtkWidget*)user_data),
		GTK_DIALOG_MODAL,
		"Ok", GTK_RESPONSE_OK,
		"Cancel", GTK_RESPONSE_CANCEL,
		NULL);

	GtkWidget* en_label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(en_label), "<i><small><small>english</small></small></i>");

	GtkWidget* en_frame = gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(en_frame), en_label);

	GtkWidget* en_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(en_frame), en_entry);	

	GtkWidget* delete_dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(delete_dialog_box), en_frame, FALSE, FALSE, 0);

	GtkWidget* content_area = gtk_dialog_get_content_area(GTK_DIALOG(delete_dialog));
	gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);
	gtk_container_add(GTK_CONTAINER(content_area), delete_dialog_box);

	gtk_widget_show_all(delete_dialog);

	GtkWidget* main_window_bottom = MAIN_WINDOW_BOTTOM((GtkWidget*)user_data);
	guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(main_window_bottom), "");
	const gchar notification[200];
	char english[WORD_SIZE], vietnamese[WORD_SIZE];
	const gchar *en_text;

	switch(gtk_dialog_run(GTK_DIALOG(delete_dialog))) {
		case GTK_RESPONSE_OK:
			en_text = gtk_entry_get_text(GTK_ENTRY(en_entry));
			strcpy(english, (char*)en_text);

			int n = delete_word(english);

			if(n == 1) sprintf((char*)notification, "_: delete/%s/ok", english);
			else sprintf((char*)notification, "_: delete/%s/failed", english);
			break;
		case GTK_RESPONSE_CANCEL:
		case GTK_RESPONSE_NONE:
		default:
			en_text = gtk_entry_get_text(GTK_ENTRY(en_entry));
			strcpy(english, (char*)en_text);
			sprintf((char*)notification, "_: delete/%s/cancel", english); 
	}

	gtk_statusbar_push(GTK_STATUSBAR(main_window_bottom), id, notification);
	gtk_widget_destroy(delete_dialog);

	return;
}

/***************************** create head ****************************/
GtkWidget* create_head(gpointer user_data)
{
	GtkWidget* head = gtk_search_entry_new();

	g_signal_connect(G_OBJECT(head), "activate", G_CALLBACK(search_entry_activate), (GtkWidget*)user_data);
	g_signal_connect(G_OBJECT(head), "key_press_event", G_CALLBACK(press_key_tab), (GtkWidget*)user_data);	

	return head;	
}

// signals emits in head
void search_entry_activate(GtkWidget* widget, gpointer user_data)
{	
	const gchar *en_text, vi_text[WORD_SIZE];
	char english[WORD_SIZE];
	char vietnamese[WORD_SIZE];

	en_text = gtk_entry_get_text(GTK_ENTRY(widget));
	strcpy(english, (char*)en_text);
	int result = search_word(english, vietnamese);

	if(result == -1) return; // co loi

	strcpy((char*)vi_text, vietnamese);

	GtkWidget* main_window_body = MAIN_WINDOW_BODY((GtkWidget*)user_data);
	GList* l = gtk_container_get_children(GTK_CONTAINER(main_window_body));
	GList* l_ = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)l->data));

	GtkWidget* result_area = (GtkWidget*)l_->data;
	g_list_free(l);
	g_list_free(l_);

	GList* list = gtk_container_get_children(GTK_CONTAINER(result_area));
	
	GtkWidget* del = (GtkWidget*)list->data;
	gtk_widget_destroy(del);
	g_list_free(list);	

	GtkWidget* h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(result_area), h_box, FALSE, FALSE, 0);

	GtkWidget* en_label = gtk_label_new(en_text);
	gtk_box_pack_start(GTK_BOX(h_box), en_label, FALSE, FALSE, 50);

	GtkWidget* vi_label = gtk_label_new(vi_text);
	gtk_box_pack_start(GTK_BOX(h_box), vi_label, FALSE, FALSE, 50);	

	gtk_widget_show_all(result_area);

	return;
}

gboolean press_key_tab(GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	const gchar* text = gtk_entry_get_text(GTK_ENTRY(widget));
	const gchar full_word[WORD_SIZE];
	char prefix[WORD_SIZE], *output[50];

	GtkWidget* main_window_body = MAIN_WINDOW_BODY((GtkWidget*)user_data);	
	GtkWidget* suggest_area = get_suggest_area(main_window_body);

	switch(event->keyval) {
		case GDK_KEY_Tab:
			clear_suggest_area(suggest_area);
			strcpy(prefix, (char*)text);
			int num = suggest_word(prefix, output);

			if(num == 1) {
				strcpy((char*)full_word, output[0]);
				gtk_entry_set_text(GTK_ENTRY(widget), full_word);
			} else {
				const gchar label_text[100];
				char frame_text[100];

				GList* l = gtk_container_get_children(GTK_CONTAINER(main_window_body));
				l = g_list_next(l);
				GtkWidget* body_frame = (GtkWidget*)l->data;
				sprintf(frame_text, "<i><small>%d results</small></i>", num);	
				strcpy((char*)label_text, frame_text);

				GtkWidget* label = gtk_label_new(NULL);
				gtk_label_set_markup(GTK_LABEL(label), label_text);
				gtk_frame_set_label_widget(GTK_FRAME(body_frame), label);

				edit_suggest(suggest_area, output, num);
				gtk_widget_show_all(body_frame);
				g_list_free(l);
			}
			break;		
		default:
			return FALSE;	
	}

	return TRUE;
}

GtkWidget* get_suggest_area(GtkWidget* main_window_body)
{
	GList *l = gtk_container_get_children(GTK_CONTAINER(main_window_body)); // box
	l = g_list_next(l);
	GList *l_ = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)l->data)); // frame

	GtkWidget* tmp = (GtkWidget*)l_->data; // scrolled window
	
	GList* l__ = gtk_container_get_children(GTK_CONTAINER(tmp));

	GList* l___ = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)l__->data)); // box in scrolled window

	GtkWidget* suggest_area = (GtkWidget*)l___->data;	

	g_list_free(l);
	g_list_free(l_);
	g_list_free(l__);
	g_list_free(l___);	

	return suggest_area;
}

void clear_suggest_area(GtkWidget* suggest_area)
{
	GList* root = gtk_container_get_children(GTK_CONTAINER(suggest_area));

	while(root) {
		gtk_widget_destroy((GtkWidget*)root->data);
		root = g_list_next(root);
	}

	g_list_free(root);

	return;
}

void edit_suggest(GtkWidget* suggest_area, char** output, int num)
{	
	for(int i = 0; i < num; i++) {
		const gchar en_text[WORD_SIZE];
		char en_word[WORD_SIZE];

		strcpy(en_word, output[i]);
		sprintf((char*)en_text, "<i>%s</i>", en_word);

		GtkWidget* en_label = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(en_label), en_text);
		GtkWidget* h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_box_pack_start(GTK_BOX(h_box), en_label, FALSE, FALSE, 20);

		gtk_box_pack_start(GTK_BOX(suggest_area), h_box, FALSE, FALSE, 3);
	}
	
	destroy(output, 50);

	return;
}

/******************************* create body ********************************/
GtkWidget* create_body(gpointer user_data)
{
	GtkWidget* body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);	

	GtkWidget* left_frame = gtk_frame_new("");
	GtkWidget* body_left = create_result_area();
	gtk_box_pack_start(GTK_BOX(body), left_frame, TRUE, TRUE, 0);	
	gtk_container_add(GTK_CONTAINER(left_frame), body_left);

//	GtkWidget* body_left = create_result_area();
//	gtk_box_pack_start(GTK_BOX(body), body_left, TRUE, TRUE, 0);

//	GtkWidget* sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
//	gtk_box_pack_start(GTK_BOX(body), sep, FALSE, FALSE, 0);

	GtkWidget* body_right = gtk_frame_new("");
	gtk_box_pack_end(GTK_BOX(body), body_right, TRUE, TRUE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(body_right), 0);

	GtkWidget* scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(body_right), scrolled);

	GtkWidget* scrolled_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(scrolled), scrolled_box);

	return body;
}

GtkWidget* create_result_area()
{
	GtkWidget* result = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 

	GtkWidget* h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(result), h_box, FALSE, FALSE, 0);

	return result;
}

/***************************** create bottom ********************************/
GtkWidget* create_bottom(gpointer user_data)
{
	GtkWidget* bottom = gtk_statusbar_new();
	
	guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(bottom), "");
	gtk_statusbar_push(GTK_STATUSBAR(bottom), id, "_: C_adv/project_1/dictionary");

	return bottom;
}







