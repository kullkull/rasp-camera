#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>
#include <time.h>
#include <math.h>
#include <form.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "picam_process.h"
#include "network_process.h"
#include "picampic_process.h"
#include "create_newwin.h"
#include "Init_Program.h"
#include "define.h"
#include "Color_Setting.h"
#include "System_Command.h"
#include "types/shared_data.h"
#include "create_newslectwin.h"



#define BACKGROUND_HEIGHT   ((LINES))
#define BACKGROUND_WIDTH   ((COLS))
#define BACKGROUND_POS_X   ((0))
#define BACKGROUND_POS_Y   ((1))
#define TITLE_HEIGHT   ((2))
#define TITLE_WIDTH   ((COLS))
#define TITLE_POS_X   ((0))
#define TITLE_POS_Y   ((1))
#define CLOCK_HEIGHT   ((1))
#define CLOCK_WIDTH   (((COLS * 1) / 4))
#define CLOCK_POS_X   ((1))
#define CLOCK_POS_Y   (((TITLE_POS_Y)+TITLE_HEIGHT + 1))
#define STATUSBAR_HEIGHT   ((2))
#define STATUSBAR_WIDTH   (((COLS * 3) / 4 - 3))
#define STATUSBAR_POS_X   ((CLOCK_POS_X + CLOCK_WIDTH + 1))
#define STATUSBAR_POS_Y   (((TITLE_POS_Y)+TITLE_HEIGHT + 1))
#define AREA_1_HEIGHT   ((LINES / 4))
#define AREA_1_WIDTH   (((COLS * 1) / 4))
#define AREA_1_POS_X   ((1))
#define AREA_1_POS_Y   ((7 * (LINES / 30)))
#define AREA_2_HEIGHT   ((LINES / 4))
#define AREA_2_WIDTH   (((COLS * 1) / 4))
#define AREA_2_POS_X   (((COLS - AREA_2_WIDTH - 1)))
#define AREA_2_POS_Y   ((7 * (LINES / 30)))
#define AREA_3_HEIGHT   ((LINES / 4))
#define AREA_3_WIDTH   (((COLS - AREA_2_WIDTH - AREA_1_WIDTH) - 4))
#define AREA_3_POS_X   (((COLS - AREA_3_WIDTH) / 2))
#define AREA_3_POS_Y   ((7 * (LINES / 30)))
#define AREA_4_HEIGHT   ((LINES / 5))
#define AREA_4_WIDTH   (((COLS * 3) / 4 - 3))
#define AREA_4_POS_X   (((COLS - AREA_3_WIDTH) / 2))
#define AREA_4_POS_Y   ((LINES - AREA_4_HEIGHT - 1))
#define SLECT_HEIGHT   ((LINES / 5))
#define SLECT_WIDTH   (((COLS) / 4))
#define SLECT_POS_X   ((1))
#define SLECT_POS_Y   ((LINES - SLECT_HEIGHT - 1))
#define AREA_5_HEIGHT   ((LINES - LINES / 4 - LINES / 5 - 10))
#define AREA_5_WIDTH   (((COLS * 1) / 4))
#define AREA_5_POS_X   ((1))
#define AREA_5_POS_Y   ((7 * (LINES / 30) + AREA_1_HEIGHT + 1))
#define AREA_6_HEIGHT   ((LINES - LINES / 4 - LINES / 5 - 10))
#define AREA_6_WIDTH   (((COLS * 1) / 4))
#define AREA_6_POS_X   (((COLS - AREA_2_WIDTH - 1)))
#define AREA_6_POS_Y   ((7 * (LINES / 30) + AREA_1_HEIGHT + 1))
#define AREA_7_HEIGHT   ((LINES - LINES / 4 - LINES / 5 - 10))
#define AREA_7_WIDTH   (((COLS - AREA_2_WIDTH - AREA_1_WIDTH) - 4))
#define AREA_7_POS_X   (((COLS - AREA_3_WIDTH) / 2))
#define AREA_7_POS_Y  ((((7 * (LINES / 30) + AREA_1_HEIGHT + 1))))





int Key_IN;
FILE* DEBUG;
int Detected;
int saveimagesuffix;
int Donotpic;
struct timespec ts;
char status_ok[10];
char status_not_ok[14];
char saveimage[MAX_ARR_SIZE_S];





int main(int argc, char* argv[])
{



    int pid;
    int pipe_fd[2];


    if (pipe(pipe_fd) == -1)
    {
        printf("pipe_create failed\n");
        exit(1);
    }
    pid = fork();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (pid == 0)
    {
        dup2(pipe_fd[1], 2);
        dup2(pipe_fd[1], 1);
        if (execl("/usr/sbin/tcpdump", "/usr/sbin/tcpdump", "-t", "-nn", "port", argv[1], NULL) == -1)
        {
            printf("NO tcpdump found please INSTALL: TCPDUMP \n apt-get install tcpdump\n");
            //exit(1);
        }



    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {


        int flag = fcntl(pipe_fd[0], F_GETFL, 0);
        fcntl(pipe_fd[0], F_SETFL, flag | O_NONBLOCK);
        key_t SHARED_KEY = msgget((key_t)SHARED_KEY_VAL, IPC_CREAT | 0666);
        if (SHARED_KEY == -1)
        {
            printf("failed to create SHARED_KEY\n");
            exit(1);
        }

        SHARED_DATA network_data;

        if (argc != 2)
        {
            printf("SERVER PORT: REQUIRED\n");
            exit(1);
        }

        //---------------------------------------------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------------------------------------------
        memset(&network_data, 0x00, sizeof(network_data));
        pthread_t network_fd, picam_fd, picampic_fd;
        char* network_arg = argv[1];
        pthread_create(&network_fd, NULL, network_process, (void*)network_arg);
        pthread_create(&picam_fd, NULL, picam_process, (void*)network_arg);
        pthread_create(&picampic_fd, NULL, picampic_process, (void*)network_arg);


        //pipe_process
        //-----------------------------------------------------------------------------------------------------------------------
        Init_Program();
        //-------------------------------------------------------------------------------------------

        //-----------------------------------------------------------------------------------------------
        
	char AREA_UPTOP_DATA[MAX_ARR_SIZE] = "Press Q to Quit";
        char AREA_CLOCK_DATA[MAX_ARR_SIZE];
        char AREA_STATUSBAR_DATA[MAX_ARR_SIZE];
        char AREA_TITLE_DATA[MAX_ARR_SIZE] = "->>>  Raspberry Pi Surveillance Camera ->>>>  Administrator Page";
        char AREA_1_DATA[MAX_ARR_SIZE] = "example";
        char AREA_2_DATA[MAX_ARR_SIZE];
        char AREA_3_DATA[MAX_ARR_SIZE];
        char AREA_4_DATA[MAX_ARR_SIZE];
        char AREA_5_DATA[MAX_ARR_SIZE];
        char AREA_6_DATA[MAX_ARR_SIZE];
        char AREA_7_DATA[MAX_ARR_SIZE];
        char SLECT_DATA[MAX_ARR_SIZE] = "SELECT OPTION";
        //--------------------------------Slection Menu----------선택메뉴만--------------------------------------
        char *MENU1[] = {
            "Sytem Status           ",
            "Choise 2               ",
            "Choice 3               ",
            "Choice 4               ",
            "Choise 5               ",
            "Choise 6               ",
            "Choise 7               "
        };

        //-----------------------------------------------------------------------------------------------------
        WINDOW* BACKGROUND;
        WINDOW* TITLE;
        WINDOW* AREA_1;
        WINDOW* AREA_2;
        WINDOW* AREA_3;
        WINDOW* AREA_4;
        WINDOW* AREA_5;
        WINDOW* AREA_6;
        WINDOW* AREA_7;
        WINDOW* SLECT_W;
        WINDOW* CLOCK;
        WINDOW* STATUSBAR;

        //-----------------------------------------------------------------------------------------------------
        BACKGROUND = create_newwin(BACKGROUND_HEIGHT, BACKGROUND_WIDTH, BACKGROUND_POS_Y, BACKGROUND_POS_X);
        TITLE = create_newwin(TITLE_HEIGHT, TITLE_WIDTH, TITLE_POS_Y, TITLE_POS_X);
        CLOCK = create_newwin(CLOCK_HEIGHT, CLOCK_WIDTH, CLOCK_POS_Y, CLOCK_POS_X);
        STATUSBAR = create_newwin(STATUSBAR_HEIGHT, STATUSBAR_WIDTH, STATUSBAR_POS_Y, STATUSBAR_POS_X);
        AREA_1 = create_newwin(AREA_1_HEIGHT, AREA_1_WIDTH, AREA_1_POS_Y, AREA_1_POS_X);
        AREA_2 = create_newwin(AREA_2_HEIGHT, AREA_2_WIDTH, AREA_2_POS_Y, AREA_2_POS_X);
        AREA_3 = create_newwin(AREA_3_HEIGHT, AREA_3_WIDTH, AREA_3_POS_Y, AREA_3_POS_X);
        AREA_4 = create_newwin(AREA_4_HEIGHT, AREA_4_WIDTH, AREA_4_POS_Y, AREA_4_POS_X);
        AREA_5 = create_newwin(AREA_5_HEIGHT, AREA_5_WIDTH, AREA_5_POS_Y, AREA_5_POS_X);
        AREA_6 = create_newwin(AREA_6_HEIGHT, AREA_6_WIDTH, AREA_6_POS_Y, AREA_6_POS_X);
        AREA_7 = create_newwin(AREA_7_HEIGHT, AREA_7_WIDTH, AREA_7_POS_Y, AREA_7_POS_X);
        SLECT_W = create_newwin(SLECT_HEIGHT, SLECT_WIDTH, SLECT_POS_Y, SLECT_POS_X);

        bkgd(COLOR_PAIR(PAIR_RED_YELLOW));
        wbkgd(BACKGROUND, COLOR_PAIR(PAIR_WHITE_BLUE)); 
        wbkgd(TITLE, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(CLOCK, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(STATUSBAR, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_1, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_2, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_3, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_4, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_5, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_6, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(AREA_7, COLOR_PAIR(PAIR_WHITE_BLACK));
        wbkgd(SLECT_W, COLOR_PAIR(PAIR_BLACK_WHITE));


        //--------------------------------------------------------------------------
        keypad(SLECT_W, TRUE);
        keypad(TITLE, TRUE);
        keypad(CLOCK, TRUE);
        keypad(STATUSBAR, TRUE);
        keypad(AREA_1, TRUE);
        keypad(AREA_2, TRUE);
        keypad(AREA_3, TRUE);
        keypad(AREA_4, TRUE);
        keypad(AREA_5, TRUE);
        keypad(AREA_6, TRUE);
        keypad(AREA_7, TRUE);

        //------------------------------------------------------------------------------------------------
        nodelay(SLECT_W, 1);
        nodelay(stdscr, 1);
        nodelay(AREA_1, 1);
        nodelay(AREA_2, 1);
        nodelay(AREA_3, 1);
        nodelay(AREA_4, 1);
        nodelay(AREA_5, 1);
        nodelay(AREA_6, 1);
        nodelay(AREA_7, 1);
        nodelay(BACKGROUND, 1);
        nodelay(STATUSBAR, 1);
        nodelay(TITLE, 1);
        nodelay(CLOCK, 1);


        MENU* Menu = create_newslectwin(SLECT_W, MENU1, SLECT_WIDTH, SLECT_HEIGHT, 2, 0, SLECT_DATA);
        printw(AREA_UPTOP_DATA);

        while (1)
        {

       
            {
            
                werase(TITLE);
                werase(CLOCK);
                werase(STATUSBAR);
                werase(AREA_1);
                werase(AREA_2);
                werase(AREA_3);
                werase(AREA_4);
                werase(AREA_5);
                werase(AREA_6);
                werase(AREA_7);


                mvwprintw(TITLE, 1, (TITLE_WIDTH - strlen(AREA_TITLE_DATA)) / 2, "%s", AREA_TITLE_DATA);
                mvwprintw(AREA_1, 0, 0, AREA_1_DATA);

                //-------------------------------------------------------------------------------------------------------------------

                sprintf(AREA_STATUSBAR_DATA, "Network status: %d, CAM STATUS: %d, Data_Trasmission: %d Detection System %d", 1, 1, 1, Detected);
                mvwprintw(STATUSBAR, 0, 0, AREA_STATUSBAR_DATA);
                //------------------------------------------------------------------------------------------------
                System_Command("date -R", AREA_CLOCK_DATA);
                mvwprintw(CLOCK, 0, 0, AREA_CLOCK_DATA);
    
                msgrcv(SHARED_KEY, &network_data, sizeof(network_data) - sizeof(long), 1, IPC_NOWAIT);
                mvwprintw(AREA_2, 0, 0, network_data.DATA1);
                mvwprintw(AREA_2, 1, 0, network_data.DATA2);
                mvwprintw(AREA_2, 2, 0, network_data.DATA3);
                mvwprintw(AREA_2, 3, 0, network_data.DATA4);
                mvwprintw(AREA_2, 4, 0, network_data.DATA5);
                mvwprintw(AREA_2, 5, 0, network_data.DATA6);
                mvwprintw(AREA_2, 6, 0, network_data.DATA7);
                mvwprintw(AREA_2, 7, 0, network_data.DATA8);
                mvwprintw(AREA_2, 8, 0, network_data.DATA9);
                //--------------------------------------------------------------------------------------------------
                System_Command("netstat -an", AREA_3_DATA);
                mvwprintw(AREA_3, 0, 0, AREA_3_DATA);
  
                read(pipe_fd[0], AREA_4_DATA, sizeof(AREA_4_DATA));
                mvwprintw(AREA_4, 0, 0, AREA_4_DATA);

                refresh();
                wrefresh(BACKGROUND);
                wrefresh(TITLE);
                wrefresh(CLOCK);
                wrefresh(STATUSBAR);
                wrefresh(AREA_1);
                wrefresh(AREA_2);
                wrefresh(AREA_3);
                wrefresh(AREA_4);
                wrefresh(AREA_5);
                wrefresh(AREA_6);
                wrefresh(AREA_7);
                wrefresh(SLECT_W);

            }


            Key_IN = wgetch(SLECT_W);
 

            switch (Key_IN)
            {
            case KEY_DOWN:
                menu_driver(Menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(Menu, REQ_UP_ITEM);
                break;
            case 'q':
                endwin();
                fclose(DEBUG);
                system("ps -ef|grep tcpdump|grep -v grep |awk '{print $2}'|xargs kill -9");
                return 0;
                break;
            }

        }
    }
}


