#ifndef UI_H
#define UI_H

void gui_show_message(const char* title, const char* message);
void gui_get_input(const char* prompt, char* buffer, int buffer_size);
void gui_show_menu(const char* title, const char** options, int option_count, int selected_index);

#endif // UI_H