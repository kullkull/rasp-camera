#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

MENU* create_newslectwin(WINDOW* SLECT_W, char** choices, int SLECT_WIDTH, int SLECT_HEIGHT, int y, int x, char SLECT_DATA[])
{

    ITEM **TABLE;
    MENU *Menu;
    MENU *Menu_o;
    int n_choices, i;
    ITEM *Current_Slected;
    n_choices = 6;
    TABLE = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i)
        TABLE[i] = new_item(choices[i], choices[i]);
    TABLE[n_choices] = (ITEM *)NULL;
    Menu = new_menu((ITEM **)TABLE);
    set_menu_win(Menu, SLECT_W);
    set_menu_sub(Menu, derwin(SLECT_W, n_choices, SLECT_WIDTH, y, x)); //(상자크기(y,x 위치 y,x)
    set_menu_mark(Menu, ">");
    mvwprintw(SLECT_W, 1, (SLECT_WIDTH - strlen(SLECT_DATA)) / 2, SLECT_DATA);
    post_menu(Menu);
    return Menu;

}
