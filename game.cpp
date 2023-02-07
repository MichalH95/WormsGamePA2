#include <iostream>
#include <unistd.h>
#include <queue>
#include <ncurses.h>

#include "menu.h"
#include "game.h"
#include "helper.h"

Game::Game()
{
	
}

Game::~Game()
{
	
}

int controlWorm(int c, Worm & w1, Worm & w2, WMap & map)
{
	switch ( c ) {
		case KEY_UP:
			if ( w1.direction() != DOWN )
				w1.turn(UP);
			break;
		case KEY_LEFT:
			if ( w1.direction() != RIGHT )
				w1.turn(LEFT);
			break;
		case KEY_DOWN:
			if ( w1.direction() != UP )
				w1.turn(DOWN);
			break;
		case KEY_RIGHT:
			if ( w1.direction() != LEFT )
				w1.turn(RIGHT);
			break;
		case 'w':
			if ( w2.direction() != DOWN )
				w2.turn(UP);
			break;
		case 'a':
			if ( w2.direction() != RIGHT )
				w2.turn(LEFT);
			break;
		case 's':
			if ( w2.direction() != UP )
				w2.turn(DOWN);
			break;
		case 'd':
			if ( w2.direction() != LEFT )
				w2.turn(RIGHT);
			break;
		case 'p':
			switch ( Menu{ "Continue", "Quit" }.run() ) {
				case 0:
					map.print();
					nodelay(stdscr, TRUE);
					w1.print('O');
					w2.print('O');
					refresh();
					break;
				case 1:
					map.deleteYummyItems();
					w1.removeFromMap();
					w2.removeFromMap();
					return 0;
				case -1:
					map.deleteYummyItems();
					w1.removeFromMap();
					w2.removeFromMap();
					return 0;
			}
			break;
	}
	return 1;
}

void Game::run(WMap & map)
{
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	nodelay(stdscr, TRUE);
	clear();
	map.print();
	Worm w1(map, 1, 5);
	w1.saveToMap();
	Worm w2(map, 2, 6);
	w2.saveToMap();
	w1.print('O');
	w2.print('O');
	map.printItem(map.generateNewYummyPos());
	map.printItem(map.generateNewYummyPos());
	refresh();
	
	while ( true ) {
		try {
			w1.movePrint();
			w2.movePrint();
		}
		catch ( EndOfGame ) {
			map.deleteYummyItems();
			w1.removeFromMap();
			w2.removeFromMap();
			endOfGameScreen(w1, w2);
			return;
		}
		w1.printScore(35);
		w2.printScore(0);
		refresh();
		usleep(220000);
		
		w1.readMoves();
		w2.readMoves();
		
		int c = getch();
		int d = 0;
		for ( int i = 0 ; i < 10 ; i++ ) {
			int tmp;
			if ( (tmp = getch()) != c ) {
				if ( isFirstWorm(c) ) {
					if ( ! isFirstWorm(tmp) ) {
						d = tmp;
					} else {
						ungetch(tmp);
					}
				}
				if ( isSecondWorm(c) ) {
					if ( ! isSecondWorm(tmp) ) {
						d = tmp;
					} else {
						ungetch(tmp);
					}
				}
				break;
			}
		}
		
		
		if ( controlWorm(c, w1, w2, map) == 0 )
			return;
		if ( controlWorm(d, w1, w2, map) == 0 )
			return;
	}
	
}

