#include <ncurses.h>
using namespace std;

extern bool gameOver;
extern bool gameOver;

extern int change[];
extern char dir;

void input(WINDOW* win,Snake* s) {
    wtimeout(win, 500);
    chtype KeyPressed = wgetch(win);
    
	switch (KeyPressed) {
	case 'a':
        if (dir == 'L') break;
        else if (dir == 'R') gameOver = 1;
        dir = 'L';
        change[0] = 0;
        change[1] = -1;
        break;
    case 'd':
        if (dir == 'R') break;
        else if (dir == 'L') gameOver = 1;
        dir = 'R';
        change[0] = 0;
        change[1] = 1;
        break;
    case 'w':
        if (dir == 'U') break;
        else if (dir == 'D') gameOver = 1;
        dir = 'U';
        change[0] = -1;
        change[1] = 0;
        break;
    case 's':
        if (dir == 'D') break;
        else if (dir == 'U') gameOver = 1;
        dir = 'D';
        change[0] = 1;
        change[1] = 0;
        break;
    case 'p':
        s->add();
        break;
    case 'x':
        gameOver = 1;
        break;
    case 'r':
        s->remove();
        break;
    case 'g':
        s->gate_count++;
        break;
	}
    
}