#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <locale.h>
#define N 2
static char *coche=
"        \n"
"  ____  \n"
" _|  |_ \n"
"|______|\n"
"O      O\n"
;


struct TCoord{
        double x;
        double y;
};
struct Player{
        struct TCoord pos;
};

void draw(struct Player jugador, char *car){
        mvprintw(LINES - jugador.pos.y, jugador.pos.x,car);
}
int
main(int argc, char *argv[]){
        struct Player j1 = {{5.,10.}};
        setlocale(LC_ALL,"");
        initscr();
        while(1){
                draw(j1,coche);
                refresh();
                do{
                        int tecla;
                        tecla = getchar();
                        switch(tecla){
                                case KEY_UP:
                                        j1.pos.y = j1.pos.y - 5;
                                        draw(j1,coche);
                                        refresh();
                                        sleep(1);
                                        j1.pos.y = j1.pos.y -5;
                                        draw(j1,coche);
                                        refresh();
                                        sleep(1);
                                        j1.pos.y = j1.pos.y+10;
                                        draw(j1,coche);
                                        refresh();
                                        break;
                                case KEY_DOWN:
                                        break;
                                case KEY_LEFT:
                                        j1.pos.x = j1.pos.x-10;
                                        draw(j1,coche);
                                        refresh();
                                        break;
                                case KEY_RIGHT:
                                        j1.pos.x = j1.pos.x+10;
                                        draw(j1,coche);
                                        refresh();
                                        break;
                        }
                }while(j1.pos.y !=0);
        }
        endwin();
        return EXIT_SUCCESS;
}
