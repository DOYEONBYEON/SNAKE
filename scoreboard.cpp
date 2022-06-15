#include <ncurses.h>
using namespace std;
bool isa = 0;
bool isb = 0;
bool isc = 0;
bool isd = 0;
extern double timer;

class Score
{
    WINDOW* score_win;
    WINDOW* mission_win;
public:
    Score()
    {
        score_win = newwin(30,50,5,60 );
        mission_win = newwin(30,50,20,60);
        box(score_win,0,0);
        //box(mission_win,0,0);
    }
    void init(Snake* s) {
        clear();
        mvwprintw(score_win, 2, 0, "B:");
        mvwprintw(score_win, 3, 0, "+:");
        mvwprintw(score_win, 4, 0, "-:");
        mvwprintw(score_win, 5, 0, "G:");
        mvwprintw(score_win, 6, 0, "TIME:");

        mvwprintw(mission_win, 2, 0, "B: 10");
        mvwprintw(mission_win, 3, 0, "+: 5");
        mvwprintw(mission_win, 4, 0, "-: 5");
        mvwprintw(mission_win, 5, 0, "G: 3");
        updateLength(s->length,s->max_length);
        updateGrowth(s->growth_count);
        updatePoison(s->poison_count);
        updateGate(s->gate_count);
        updateTime(timer);
        wrefresh(score_win);
        wrefresh(mission_win);
    }
    void updateLength(int length, int max_length)
    {
        mvwprintw(score_win, 2, 4, "(%i) / (%i)", length, max_length);
        if (length >= 10) {
            mvwprintw(mission_win, 2, 6, "(V)");  
            isa = 1;  
        }
            
            
    }
    void updateGrowth(int growth)
    {
        mvwprintw(score_win, 3, 4, "%i", growth);
        if (growth >= 5) {
            mvwprintw(mission_win, 3, 6, "(V)");
            isb = 1;
        }
    }
    void updatePoison(int poison)
    {
        mvwprintw(score_win, 4, 4, "%i", poison);
        if (poison >= 5) {
            mvwprintw(mission_win, 4, 6, "(V)");   
            isc = 1; 
        }
            
    }
    void updateGate(int gate)
    {
        mvwprintw(score_win, 5, 4, "%i", gate);
        if (gate >= 3) {
            mvwprintw(mission_win, 5, 6, "(V)");
            isd = 1;
        }
            
    }
    void updateTime(int time) {
        mvwprintw(score_win, 6,6, "%i", time);
    }
    void refresh()
    {
        wrefresh(score_win);
        wrefresh(mission_win);
    }
    void clear()
    {
        wclear(score_win);
    }
};