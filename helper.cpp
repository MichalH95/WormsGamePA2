#include <ncurses.h>
#include <cstring>
#include <unistd.h>
#include <string>

#include "worm.h"
#include "helper.h"

using namespace std;

void printFrame()
{
	int maxx = getmaxx(stdscr);
	int maxy = getmaxy(stdscr);
	
	const char frameChar = 'X';
	for ( int i = 0 ; i < maxx ; i++ ) {
		mvaddch(0,i,frameChar);
		mvaddch(maxy-1,i,frameChar);
	}
	for ( int i = 0 ; i < maxy ; i++ ) {
		mvaddch(i,0,frameChar);
		mvaddch(i,maxx-1,frameChar);
	}
}

void printError(const char * err)
{
	clear();
	
	printFrame();
	
	init_pair(2, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	attron(A_BOLD);
	mvprintw(getmaxy(stdscr)*2/3, getmaxx(stdscr)/2-strlen(err)/2, err);
	refresh();
	attroff(A_BOLD);
	attroff(COLOR_PAIR(2));
	sleep(2);
}

bool isFirstWorm(int c)
{
	return c == KEY_DOWN || c == KEY_UP || c == KEY_LEFT || c == KEY_RIGHT;
}

bool isSecondWorm(int c)
{
	return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

void endOfGameScreen(const Worm & w1, const Worm & w2)
{
	int maxx = getmaxx(stdscr);
	int maxy = getmaxy(stdscr);
	
	clear();
	
	// print frame /////////////
	const char frameChar = 'X';
	for ( int i = 0 ; i < maxx ; i++ ) {
		mvaddch(0,i,frameChar);
		mvaddch(maxy-1,i,frameChar);
	}
	for ( int i = 0 ; i < maxy ; i++ ) {
		mvaddch(i,0,frameChar);
		mvaddch(i,maxx-1,frameChar);
	}
	/////////////////////////
	
	int xcoord = maxx/2-7;
	int ycoord = maxy*0.4;
	attron(A_BOLD);
//	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	
	
	if ( w1.score() > w2.score() ) {
		attron(COLOR_PAIR(w1.color()));
		mvprintw(ycoord, xcoord, (std::string("PLAYER ") + std::to_string(w1.playerNum()) + " WON!").c_str());
		attroff(COLOR_PAIR(w1.color()));
	} else if ( w1.score() < w2.score() ) {
		attron(COLOR_PAIR(w2.color()));
		mvprintw(ycoord, xcoord, (std::string("PLAYER ") + std::to_string(w2.playerNum()) + " WON!").c_str());
		attroff(COLOR_PAIR(w2.color()));
	} else {
		mvprintw(ycoord, xcoord, "  NOONE WON! ");
	}
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
	
	refresh();
	sleep(4);
}

void controlsScreen()
{
	int maxx = getmaxx(stdscr);
	int maxy = getmaxy(stdscr);
	
	clear();
	
	// print frame /////////////
	const char frameChar = 'X';
	for ( int i = 0 ; i < maxx ; i++ ) {
		mvaddch(0,i,frameChar);
		mvaddch(maxy-1,i,frameChar);
	}
	for ( int i = 0 ; i < maxy ; i++ ) {
		mvaddch(i,0,frameChar);
		mvaddch(i,maxx-1,frameChar);
	}
	/////////////////////////
	
	int yshift = maxy*0.2;
	int shift = yshift-1;
	
	const char * items[] = { "Player1 (green):  Arrow keys", "Player2 (purple):  W, A, S, D", "Pause game: P", "Quit menu: Q" };
	
	init_pair(7, COLOR_GREEN, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
	for ( int i = 0 ; i < 4 ; i++ ) {
		if ( i == 0 )
			attron(COLOR_PAIR(7));
		if ( i == 1 )
			attron(COLOR_PAIR(8));
		
		int xcoord = maxx/2-strlen(items[i])/2;
		int ycoord = yshift;
		yshift += shift;
		mvprintw(ycoord, xcoord, items[i]);
		if ( i == 0 )
			attroff(COLOR_PAIR(7));
		if ( i == 1 )
			attroff(COLOR_PAIR(8));
	}
	
	refresh();
	sleep(4);
}

