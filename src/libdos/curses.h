#ifndef LIBDOS_CURSES_H
#define LIBDOS_CURSES_H

#include <conio.h>

typedef unsigned short chtype;

typedef struct WINDOW WINDOW;
struct WINDOW
{
    int row;
    int col;
    int rows;
    int cols;
    int y;
    int x;
    WINDOW *parent;
    chtype bkgd;
    chtype data[80*25];
};

extern WINDOW * const stdscr;
extern chtype colpairs[];

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

#define timeout(x) setdelay((x))
#define wgetch(x) getch()
#define curs_set(x) setcursor((x))

#define raw()
#define nonl()
#define noecho()
#define keypad(x, y)
#define start_color()
#define leaveok(x, y)

#define ERR -1
#define OK 0
#define COLOR_PAIRS 64

#define COLOR_PAIR(x) colpairs[(x)]

#define getyx(win, uy, ux) do { (uy) = (win)->y; (ux) = (win)->x; } while (0)
#define getparyx(win, uy, ux) do { \
    if (!((win)->parent)) { (uy) = -1; (ux) = -1; } \
    else { (uy) = (win)->row - (win)->parent->row; \
	(ux) = (win)->col - (win)->parent->col; } \
    } while (0)
#define getbegyx(win, uy, ux) \
    do { (uy) = (win)->row; (ux) = (win)->col; } while (0)
#define getmaxyx(win, uy, ux) \
    do { (uy) = (win)->rows; (ux) = (win)->cols; } while (0)

#define wmove(win, uy, ux) do { (win)->y = (uy); (win)->x = (ux); } while (0)
#define move(uy, ux) wmove((uy), (ux))

#define A_BOLD 0x0800U
#define A_BLINK 0x8000U
#define A_ALTCHARSET 0

WINDOW *initscr(void);
int endwin(void);

WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
WINDOW *subwin(WINDOW *orig, int nlines, int nclos, int begin_y, int begin_x);

int delwin(WINDOW *win);

#define refresh() wrefresh(stdscr)
int wrefresh(WINDOW *win);
int wnoutrefresh(WINDOW *win);
int doupdate(void);

#define bkgd(x) wbkgd(stdscr, (x))
int wbkgd(WINDOW *win, chtype ch);

#define clear() wclear(stdscr)
#define wclear(x) werase((x))
#define erase() werase(stdscr)
int werase(WINDOW *win);

#define addch(x) waddch(stdscr, (x))
int waddch(WINDOW *win, chtype ch);
#define mvaddch(y, x, ch) mvwaddch(stdscr, (y), (x), (ch))
int mvwaddch(WINDOW *win, int y, int x, const chtype ch);

int init_pair(short pair, short f, short b);

#endif