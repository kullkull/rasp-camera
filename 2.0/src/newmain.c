#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "create_newwin.h"
#include "create_newslectwin.h"


#define ARRAY_SIZE(A)	(sizeof(A)/sizeof(A[0]))

#define _DEBUG_MODE

#define SLECT_HEIGHT   (LINES / 5)
#define SLECT_WIDTH   (COLS / 4)
#define SLECT_POS_X   (1)
#define SLECT_POS_Y   (LINES - SLECT_HEIGHT - 1)

int main(int argc, char* argv[])
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	

	WINDOW* SLECT_W = create_newwin(SLECT_HEIGHT, SLECT_WIDTH, SLECT_POS_Y, SLECT_POS_X);
	//wbkgd(SLECT_W, COLOR_PAIR(PAIR_BLACK_WHITE));
	keypad(SLECT_W, TRUE);
	nodelay(SLECT_W, 1);
	

	char *menu_list[] = {
			"Server - On [ Background Run ( Silent Mode ) ] ",
#ifdef	_DEBUG_MODE
			"Server - Debugging Mode - On",
#endif
			"Default Settings",
			"About",
			
			"Advanced Option",
			"Exit"
		};
	int n_choices = ARRAY_SIZE(menu_list);
	mvprintw(n_choices + 2 , 0, "Select and Enter");	

	ITEM **my_items =(ITEM **)calloc(n_choices + 1, sizeof(ITEM *));			
		
	for(int i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(menu_list[i],NULL);
	my_items[n_choices] = (ITEM *)NULL;


	MENU* my_menu = create_newslectwin(SLECT_W, menu_list, SLECT_WIDTH, SLECT_HEIGHT, 2, 0, "Choise");
	//MENU* my_menu = new_menu(my_items);
	post_menu(my_menu);
	refresh();
	wrefresh(SLECT_W);


	int c;
	while(true)
	{   switch(c=wgetch(SLECT_W))
	    {	case KEY_DOWN:
		        	menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
		case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		case 	 10:	//Enter
				mvprintw(n_choices + 3,0,item_name(current_item(my_menu)));
				sleep(0.3);
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				endwin();
				if(!strcmp("Server - On [ Background Run ( Silent Mode ) ] ",item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
#ifdef	_DEBUG_MODE		
				else if(!strcmp("Server - Debugging Mode - On",item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
#endif
				else if(!strcmp("Default Settings",item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp("Advanced Option",item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp("Exit",item_name(current_item(my_menu))))
					return 0;
				break;

		case 	 27: 	//ESC
		case 	'q':
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				endwin();
				return 0;
				break;

	
		}
	}	

	
}


