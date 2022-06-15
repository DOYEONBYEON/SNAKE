#include <ncurses.h>
#include "gate.cpp"
using namespace std;

#define WALL '#'
#define IM_WALL ACS_CKBOARD
#define HEAD ACS_DIAMOND
#define BODY 'o'

extern char dir;
extern int change[];
extern bool gameOver;

class SnakeNode
{
public:
    int x, y;
    int prev_x, prev_y;
    SnakeNode * next;
    SnakeNode * prev;
    int icon;
};

class Snake
{
public:
    int length , max_length ,  growth_count, poison_count ,  gate_count;
    SnakeNode * H;
    SnakeNode * T;
    void move(Snake* s,WINDOW* win, Gate& gate1, Gate& gate2);
    void add();
    void remove();
    //void add();
};

//-----------------------------------------------------------------
void Snake::move(Snake* s, WINDOW* win, Gate& gate1, Gate& gate2) {
    SnakeNode* sn = s->H;
    sn->prev_x = sn->x;
    sn->prev_y = sn->y;
    sn->y += change[0];
    sn->x += change[1];

    if (sn->y == gate1.pos_y  and sn->x == gate1.pos_x){
        s->gate_count ++;
        if(gate2.pos_x == 0){
            dir = 'R';
            change[0] = 0;
            change[1] = 1;
        }
        else if(gate2.pos_x == 41) {
            dir = 'L';
            change[0] = 0;
            change[1] = -1;
        }
        else if(gate2.pos_y == 0) {
            dir = 'D';
            change[0] = 1;
            change[1] = 0;
        }
        else if(gate2.pos_y == 20) {
            dir = 'U';
            change[0] = -1;
            change[1] = 0;
        }
        sn->x = gate2.pos_x;
        sn->y = gate2.pos_y;
        
    }
    else if (sn->y == gate2.pos_y  and sn->x == gate2.pos_x){
        s->gate_count ++;
        if(gate1.pos_x == 0){
            dir = 'R';
            change[0] = 0;
            change[1] = 1;
        }
        else if(gate1.pos_x == 41) {
            dir = 'L';
            change[0] = 0;
            change[1] = -1;
        }
        else if(gate1.pos_y == 0) {
            dir = 'D';
            change[0] = 1;
            change[1] = 0;
        }
        else if(gate1.pos_y == 20) {
            dir = 'U';
            change[0] = -1;
            change[1] = 0;
        }
        sn->x = gate1.pos_x;
        sn->y = gate1.pos_y;
    }

    if ( mvwinch(win, sn->y,sn->x) == WALL || mvwinch(win, sn->y,sn->x) == IM_WALL || mvwinch(win, sn->y,sn->x) == BODY) {
        gameOver = 1;
        return;
    }
    
    
    sn = sn->next;

    while(sn) {
        sn->prev_x = sn->x;
        sn->prev_y = sn->y;
        sn->x = sn->prev->prev_x;
        sn->y = sn->prev->prev_y;
        sn = sn->next;
    }
}

void Snake::add() {
    SnakeNode* sn = (SnakeNode *)malloc(sizeof(SnakeNode));
    this->T->next = sn;
    sn->prev =this->T;
    sn->x = T->prev_x;
    sn->y = T->prev_y;
    sn->prev_x= sn->x;
    sn->prev_y= sn->y;
    sn->next = NULL;
    this->T = sn;
    (this->length)++;
    if (this->length > this->max_length) this->max_length = this->length;
    (this->growth_count)++;
}
void Snake::remove() {
    (this->length)--;
    (this->poison_count)++;
    SnakeNode* node = this->T;
    node->prev->next = NULL;
    this->T = node->prev; 
    delete node;
}