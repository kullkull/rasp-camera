

#define PAIR_BLACK_WHITE        1
#define PAIR_WHITE_BLACK        2
#define PAIR_RED_BLUE           3
#define PAIR_WHITE_BLUE         4
#define PAIR_RED_YELLOW         5

#define BRIGHT_WHITE 15
#define BRIGHT_BLUE 12
#define BRIGHT_YELLOW 7
#define SKY_BLUE        14

#include <ncurses.h>

void Color_Setting(void)
{
    //-----------------흰색 글자 검정 파탕---------------------------------------------

    if (can_change_color() && COLORS >= 16)
    {
        init_color(BRIGHT_WHITE, 1000, 1000, 1000);
    }
    if (COLORS >= 16)
    {
        init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, BRIGHT_WHITE);
    }
    else
    {
        init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
    }
    //-----------------글자흰색  배경파랑색  생성-------------------------------------------
    if (can_change_color() && COLORS >= 16)
    {
        init_color(BRIGHT_BLUE, 100, 100, 1000);
    }
    if (COLORS >= 16)
    {
        init_pair(PAIR_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
    }
    else
    {
        init_pair(PAIR_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
    }
    //-------------------하늘색 생성------------------------------------------


    if (can_change_color() && COLORS >= 16)
    {
        init_color(SKY_BLUE, 100, 100, 1000);
    }
    if (COLORS >= 16)
    {
        init_pair(PAIR_RED_BLUE, COLOR_RED, SKY_BLUE);
    }
    else
    {
        init_pair(PAIR_RED_BLUE, COLOR_RED, COLOR_BLUE);
    }

    //--------------------배경검은색글자흰색--------------------------------------------------


    if (can_change_color() && COLORS >= 16)
    {
        init_color(SKY_BLUE, 100, 100, 1000);
    }
    if (COLORS >= 16)
    {
        init_pair(PAIR_WHITE_BLACK, BRIGHT_WHITE, COLOR_BLACK);
    }
    else
    {
        init_pair(PAIR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    }

    //--------------------노랑빨강--------------------------------------------------


    if (can_change_color() && COLORS >= 16)
    {
        init_color(BRIGHT_YELLOW, 1000, 1000, 1000);
    }
    if (COLORS >= 16)
    {
        init_pair(PAIR_RED_YELLOW, COLOR_RED, BRIGHT_YELLOW);
    }
    else
    {
        init_pair(PAIR_RED_YELLOW, COLOR_RED, COLOR_YELLOW);
    }


}
