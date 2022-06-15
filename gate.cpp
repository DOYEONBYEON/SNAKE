#include <ncurses.h>
using namespace std;

class Gate 
{
public:
    int pos_x; 
    int pos_y;
    int num;
    Gate(WINDOW* win, int num) {
        this->num = num;
        while(1) {
            int x = rand() % 42;
            int y = rand() % 21;
            if (mvwinch(win, y, x) == '#') {
                pos_x = x;
                pos_y = y;
                break;
            }
        }
    }
    void draw_gate(WINDOW* win) {
        mvwaddch(win,pos_y,pos_x,'O');
        mvwaddch(win,pos_y,pos_x,'O');
    }
};