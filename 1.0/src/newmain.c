#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_SIZE(A)	(sizeof(A)/sizeof(A[0]))

int main(int argc, char* argv[])
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	char *menu_list[] = {
			"Server - On [ Background Run ( Silent Mode ) ] ",
			"Server - Debugging Mode - On",
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

	MENU* my_menu = new_menu(my_items);
	post_menu(my_menu);
	refresh();

	int c;
	while(true)
	{   switch(c=getch())
	    {	case KEY_DOWN:
		        	menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
		case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		case 	 10:	//Enter
				mvprintw(n_choices + 3,0,item_name(current_item(my_menu)));
				sleep(1);
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				endwin();
				if(!strcmp(menu_list[0],item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));				
				else if(!strcmp(menu_list[1],item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp(menu_list[2],item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp(menu_list[3],item_name(current_item(my_menu))))
					execl("/bin/ls"," ",((char *)NULL));
				else if(!strcmp(menu_list[4],item_name(current_item(my_menu))))
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


