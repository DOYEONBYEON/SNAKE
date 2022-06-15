#include <ncurses.h>
using namespace std;
class item
{
public:
    int pos_x, pos_y;
    char name;
    bool exi; 
    item(WINDOW* win , char c) {
        exi = true;
        name = c;

        while(1) {
            int x = rand() % 42;
            int y = rand() % 21;
            if (mvwinch(win, y, x) == ' ') {
                pos_x = x;
                pos_y = y;
                break;
            }
        }
    }
    void draw_item(WINDOW* win) {
        mvwaddch(win,pos_y,pos_x,name);
    }

    void repos(WINDOW* win) {
        while(1) {
            int x = rand() % 42;
            int y = rand() % 21;
            if (mvwinch(win, y, x) == ' ') {
                pos_x = x;
                pos_y = y;
                break;
            }
        }
    }
};