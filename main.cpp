#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h> 
#include <string>

#include "snake.cpp"
#include "item.cpp"
#include "scoreboard.cpp"
#include "input.cpp"
#include "drawsetup.cpp"
using namespace std;

int stime = 0;
int itime = 0;
int isGate = 0;
double timer = 0;
double itimer = 0;
bool gameOver;
bool Win = 0;
int change[2] = {1,0};
char dir;

void init(Snake* s, int y, int x) {
    SnakeNode* sn = (SnakeNode *)malloc(sizeof(SnakeNode));
    s->H = sn; s->T = sn;
    sn->x = x; sn->y = y;
    sn->prev_x = x; sn->prev_y = y;
    sn->next = NULL;
    sn->prev = NULL;
    s->length = 1;
    s->max_length = 1;
    s->poison_count = 0;
    s->growth_count = -2;
    s->gate_count = 0;
}


int main() {
    initscr();
    resizeterm(600,1000);
    
    noecho();
    curs_set(0);

    WINDOW *win = newwin(21,42, 5,5);
    
    wrefresh(win);
    SetUp(win,5);
    
    wrefresh(win);
    int map_ch = 1;
    int posx, posy;
    while(1) {
        
        mvwprintw(win, 20, 1, "Press 1 or 2 or 3 or 4 to choose map");
        wrefresh(win);
        char input = getchar();
        if(input == 'x') {
            gameOver = 1;break; 
        }
        else if(input == '1') {
            map_ch = 1;
            posy = 6;
            posx = 20;
            break; 
        }
        else if(input == '2') {
            map_ch = 2;
            posy = 15;
            posx = 15;
            break; 
        }
        else if(input == '3') {
            map_ch = 3;
            posy = 15;
            posx = 15;
            break; 
        }
        else if(input == '4') {
            map_ch = 4 ;
            posy = 10;
            posx = 20;
            break; 
        }
    }
    Snake s;
    init(&s,posy,posx);
    gameOver = 0;
    s.add();
    s.add();

    Score scoreboard = Score();
    scoreboard.init(&s);



    SetUp(win,map_ch);
    item apple(win, 'A');
    item poison(win, 'P');
    Gate gate1(win, 1);
    Gate gate2(win, 2);
    draw(win, &s, apple, poison, gate1, gate2);
    
    while(!gameOver) 
    {
        time_t start, end;
        start = time(NULL);

        input(win,&s);
        s.move(&s,win, gate1, gate2);
        if(s.length < 3) gameOver = 1; 
        draw(win, &s, apple, poison, gate1, gate2);
        stime ++;
        itime ++;
        if (stime > 10) {
            
            isGate = 1;
        } 
        if (itimer > 5) {
            apple.repos(win);
            poison.repos(win);
            itimer = 0;
        } 
        scoreboard.init(&s);
        if( isa and isb and isc and isd) {
            Win = 1;
        }

        end = time(NULL);
        timer += difftime(end,start);
        itimer += difftime(end,start);

        if (Win ) {
            wclear(win);
            mvwprintw(win, 10, 1, "YOU WIN!  PRESS ANY KEY TO NEXT STAGE");
            wrefresh(win);
            getchar();
            scoreboard.clear();
            Win = 0;
            while(s.length >= 4) {s.remove();}
            s.max_length = 3;
            s.growth_count = 0;
            s.poison_count = 0;
            s.gate_count = 0;
            isa = isb = isc = isd = 0;
            SetUp(win,++map_ch);
        }
    }
    
    if(gameOver and !Win) {
        scoreboard.clear();
        wclear(win);
        SetUp(win,6);
    }
    wrefresh(win);
    scoreboard.refresh();
    
    getchar();
    return 0;
}