#include <ncurses.h>


WINDOW *create_newwin(int TITLE_HEIGHT, int TITLE_WIDTH, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(TITLE_HEIGHT, TITLE_WIDTH, starty, startx);
    wrefresh(local_win);
    return local_win;
}
