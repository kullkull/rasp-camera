#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "Color_Setting.h"

extern FILE* DEBUG;
extern struct timespec ts;
void Init_Program(void)
{
    // INTITIALIZATION
    initscr(); //이걸 활성화시켜야지 그래픽 모드 작동댐
    raw();  //사용자가 엔터키를 안눌러도 글자 전달댐
    keypad(stdscr, TRUE); //특수키를 입력 받을지의 여부, ex F1,F2~F12같은 거
    noecho(); //사용자가 입력해도 화면에, 지저분하게 뜨지 않음
              //cbreak();
    refresh(); //반드시 해야함 LINES, COLS을 업데이트 함
    start_color();// 색갈을 사용함
    Color_Setting();
    //halfdelay(1);
    //cbreak();
    //nobreak();
    memset(&ts, 0, sizeof(ts));
    DEBUG = fopen("Debug_Result.txt", "w");
}

