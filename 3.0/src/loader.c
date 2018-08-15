#define _DEBUG_MODE

#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "window.h"
#include "settings.h"


#define ARRAY_SIZE(A)	(sizeof(A)/sizeof(A[0]))
#define _WAIT	sleep(0.3)
#define SLECT_HEIGHT  6
#define SLECT_WIDTH   50
#define SLECT_POS_X   5
#define SLECT_POS_Y   4

int main(int argc, char* argv[])
{

//Checking Required Devices....
_WAIT;


//Loading Raspi - Loader ! 
int settings[]={
		9190,//port
		52, //data width
		52, //data height
		1, //google push alarm
		0	//nothing....
		};
	initscr();
	cbreak();
	noecho();
	read_settings(settings);
	start_color();
	keypad(stdscr, TRUE);
	
WINDOW* SLECT_W = create_window(SLECT_HEIGHT, SLECT_WIDTH, SLECT_POS_Y, SLECT_POS_X);

	init_pair(15, COLOR_WHITE, COLOR_BLUE);
	bkgd(COLOR_PAIR(15));
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
	char str[30];

	mvprintw(1 , 0, "Raspberry Pi - Camera Server Loader !");	
	mvprintw(2 , 0, "Select and Enter");
	
	sprintf(str,"Default port: %d",settings[0]);
	mvprintw(n_choices +5, 0 ,str);

	sprintf(str,"Data width: %d",settings[1]);
	mvprintw(n_choices +6, 0 ,str);
	
	sprintf(str,"Data height: %d",settings[2]);
	mvprintw(n_choices +7, 0 ,str);

	sprintf(str,"Google Push: %d",settings[3]);
	mvprintw(n_choices +8, 0 ,str);	

	ITEM **my_items =(ITEM **)calloc(n_choices + 1, sizeof(ITEM *));			
		
	for(int i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(menu_list[i],NULL);
	my_items[n_choices] = (ITEM *)NULL;


	MENU* my_menu = new_menu((ITEM **)my_items);
	set_menu_win(my_menu,SLECT_W);
	set_menu_mark(my_menu,"+");
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
				_WAIT;
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				endwin();
				if(!strcmp("Server - On [ Background Run ( Silent Mode ) ] ",item_name(current_item(my_menu))))
					execl("bin/core","bin/core","9190",((char *)NULL));
#ifdef	_DEBUG_MODE		
				else if(!strcmp("Server - Debugging Mode - On",item_name(current_item(my_menu))))
					execl("bin/essentials","bin/essentials","9190",((char *)NULL)    );
#endif
				else if(!strcmp("Default Settings",item_name(current_item(my_menu))))
					default_settings();
				else if(!strcmp("Advanced Option",item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp("About",item_name(current_item(my_menu))))
					execl("/bin/cat","cat",".credit",((char *)NULL));


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


