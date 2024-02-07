#include <curses.h>

#include <stdlib.h>

#include <time.h>

#define GRASS      ' '

#define WATER      '~'

#define MOUNTAIN   'A'

#define PLAYER     '#'

#define TREE       'Y'

#define BLACKGRASS 'I'

#define BRIGE      '-'

#define DIMOND     'V'

#define GRASS_PAIR      1

#define EMPTY_PAIR      1

#define WATER_PAIR      2

#define MOUNTAIN_PAIR   3

#define PLAYER_PAIR     4

#define TREE_PAIR       8

#define BLACKGRASS_PAIR 10

#define BRIGE_PAIR      5

#define DIMOND_PAIR     6

int is_move_okay(int y, int x);

void draw_map(void);

int main(void)

{

    int y, x, time;

    int ch;

    /* 初始化curses */

    initscr();

    keypad(stdscr, TRUE);

    cbreak();

    noecho();

    curs_set(0); //把光标置为不可见

    /* 初始化颜色 */

    if (has_colors() == FALSE) {

        endwin();

        printf("Your terminal does not support color\n");

        exit(1);

    }

    start_color();

    init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);

    init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);

    init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);

    init_pair(PLAYER_PAIR, COLOR_RED, COLOR_BLACK);

    init_pair(TREE_PAIR, COLOR_BLACK, COLOR_GREEN);

    init_pair(BLACKGRASS_PAIR, COLOR_BLACK, COLOR_BLUE);

    init_pair(BRIGE_PAIR, COLOR_GREEN, COLOR_BLACK);

    init_pair(DIMOND_PAIR, COLOR_BLUE, COLOR_WHITE);

    clear();

    /* 初始化探索地图 */

    draw_map();


    mvprintw(0, 0, "                                                                      Welcome!                                                                                         ");

    /* 在左下角创建新角色 */

    y = 2;

    x = 50;

    do {

        /* 默认情况下你获得了一个闪烁的光标--用来指明玩家 * */

        attron(COLOR_PAIR(PLAYER_PAIR));

        mvaddch(y, x, PLAYER);

        attroff(COLOR_PAIR(PLAYER_PAIR));

        //move(y, x);

        refresh();

        ch = getch();

        /* 测试输入键值并获取方向 */

        switch (ch) {

        case KEY_UP:

        case 'w':

        case 'W':

            if ((y > 0) && is_move_okay(y - 1, x)) {

		attron(COLOR_PAIR(GRASS_PAIR));

		mvaddch(y, x, GRASS);

		attroff(COLOR_PAIR(GRASS_PAIR));

                y = y - 1;

            }

            break;

        case KEY_DOWN:

        case 's':

        case 'S':

            if ((y < LINES - 1) && is_move_okay(y + 1, x)) {

		attron(COLOR_PAIR(GRASS_PAIR));

		mvaddch(y, x, GRASS);

		attroff(COLOR_PAIR(GRASS_PAIR));

                y = y + 1;

            }

            break;

        case KEY_LEFT:

        case 'a':

        case 'A':

            if ((x > 0) && is_move_okay(y, x - 1)) {

		attron(COLOR_PAIR(GRASS_PAIR));

		mvaddch(y, x, GRASS);

		attroff(COLOR_PAIR(GRASS_PAIR));

                x = x - 1;

            }

            break;

        case KEY_RIGHT:

        case 'd':

        case 'D':

            if ((x < COLS - 1) && is_move_okay(y, x + 1)) {

		attron(COLOR_PAIR(GRASS_PAIR));

		mvaddch(y, x, GRASS);

		attroff(COLOR_PAIR(GRASS_PAIR));

                x = x + 1;
            }

            break;

        }
	time++;
	if(time > 10)
	{
		draw_map();
		time = 0;
	}

    }

    while ((ch != 'q') && (ch != 'Q') || (x != 0) || (y != 0));

    mvprintw(0, 0, "                                                                                        quit                                                         ");

    refresh();

    sleep(1);

    endwin();

    exit(0);

}

int is_move_okay(int y, int x)

{

    int testch;

    /* 当空白处可以进入的时候返回true */

    testch = mvinch(y, x);

    return (((testch & A_CHARTEXT) == GRASS)

	 || ((testch & A_CHARTEXT) == BLACKGRASS)

         || ((testch & A_CHARTEXT) == BRIGE)

         || ((testch & A_CHARTEXT) == PLAYER)

	 || ((testch & A_CHARTEXT) == WATER && (getch() == 's'))

         || ((testch & A_CHARTEXT) == MOUNTAIN && (getch() == 'x'))

         || ((testch & A_CHARTEXT) == TREE && (getch() == 't')));

}

void draw_map(void)

{

    int y, x;

    /* 绘制探索地图 */

    /* 背景 */

    attron(COLOR_PAIR(GRASS_PAIR));

    for (y = 0; y < LINES; y++) {

        mvhline(y, 0, GRASS, COLS);

    }

    attroff(COLOR_PAIR(GRASS_PAIR));

    /* 山峰和山路 */

    attron(COLOR_PAIR(MOUNTAIN_PAIR));

    for (x = COLS / 2; x < COLS * 3 / 4; x++) {

        mvvline(0, x + 7, MOUNTAIN, LINES);

    }

    attroff(COLOR_PAIR(MOUNTAIN_PAIR));

    attron(COLOR_PAIR(GRASS_PAIR));

    mvhline(LINES / 4, 0, GRASS, COLS);

    attroff(COLOR_PAIR(GRASS_PAIR));

    /* 湖和桥 */

    attron(COLOR_PAIR(WATER_PAIR));

    for (y = 1; y < LINES / 5; y++) {

        mvhline(y + 10, 1, WATER, COLS / 3);

    }
    
    attroff(COLOR_PAIR(WATER_PAIR));

    attron(COLOR_PAIR(BRIGE_PAIR));

    mvvline(11, 14, BRIGE, LINES / 5 - 1);

    attroff(COLOR_PAIR(BRIGE_PAIR));


    /* 水稻 */
    
    attron(COLOR_PAIR(BLACKGRASS_PAIR));

    for(y = 1; y < 8; y++){

	    mvhline(y, 14, BLACKGRASS, COLS / 3);    
    
    }

    attroff(COLOR_PAIR(BLACKGRASS_PAIR));

    /* 树 */

    attron(COLOR_PAIR(TREE_PAIR));

    for(y = 0; y < COLS / 3; y++){
	   mvhline(y / 10, 5, TREE, COLS / 7);
    }

    mvvline(0, 40, TREE, 10);

    mvvline(0, 80, TREE, 11);

    mvhline(10, 40, TREE, 40);

    attroff(COLOR_PAIR(TREE_PAIR));
  
    /* 钻石 */

    attron(COLOR_PAIR(DIMOND_PAIR));

    srand((unsigned)time(NULL));

    for(y = 0; y < 3; y++){
           mvhline(y + 20, COLS / 2 + 25, DIMOND, 3);
    }

    attroff(COLOR_PAIR(DIMOND_PAIR));


}
