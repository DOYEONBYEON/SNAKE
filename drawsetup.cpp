#include <ncurses.h>
#include <fstream>
extern int isGate ;
using namespace std;
int SnakeMap[21][42];
string map[6] = {"map1.txt" , "map2.txt" , "map3.txt", "map4.txt", "snakegame.txt" , "gameover.txt"};


void draw_map(WINDOW* win) {
    for(int i=0; i<21; i++){
        for (int j=0; j<42; j++) {
            switch(SnakeMap[i][j]) {
                case 1:
                    mvwaddch(win,i,j, WALL);
                    break;
                case 2: 
                    mvwaddch(win,i,j, IM_WALL);
                    break;
                case 0:
                    mvwaddch(win,i,j, ' ');
                    break;
            }
        }
  	}
}
void clear_map(WINDOW* win) {
    for(int i=0; i<21; i++){
        for (int j=0; j<42; j++) {
            mvwaddch(win,i,j, ' ');
        }
  	}
}

//-----------------------------------------------------------------
void SetUp(WINDOW *win, int n) {              //맵 그림
    char c;
    ifstream file(map[n-1]);
    if(file.is_open()){
		for (int i=0; i<21; i++){
        	for (int j=0; j<42; j++){
          	    file.get(c);
			    if( c <= '0' || c >= '9' ) file.get(c);
	            SnakeMap[i][j] = c-'0'; // char -> int
        	}
     	}
  	}
    file.close(); // 열었던 파일을 닫는다.
    draw_map(win);
}

//-----------------------------------------------------------------
void draw(WINDOW* win, Snake* s, item& apple, item& poison, Gate& gate1, Gate& gate2) {  
    SnakeNode *k = s->H;

    if ( mvwinch(win, k->y,k->x) == WALL || mvwinch(win, k->y,k->x) == IM_WALL || mvwinch(win, k->y,k->x) == BODY) {
        gameOver = 1;
        return;
    }
    if (mvwinch(win, k->y,k->x) == 'A') {
        s->add(); apple = item(win, 'A');
    }
    if (mvwinch(win, k->y,k->x) == 'P'){
        s->remove(); poison = item(win, 'P');
    } 

    clear_map(win);
    wrefresh(win);
    draw_map(win);  //맵 그림
    
    mvwaddch(win,k->y,k->x, HEAD);
    k = k->next;
    while(k != NULL) {
        mvwaddch(win,k->y,k->x, BODY);
        k = k->next;
    }

    apple.draw_item(win);
    poison.draw_item(win);
    if (isGate == 1) {
        gate1.draw_gate(win);
        gate2.draw_gate(win);
    }

    
    wrefresh(win);
}