#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

#include "menu.h"
#include "wmap.h"
#include "game.h"
#include "worm.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv)
{
//	if ( ! system(NULL) ) {
//		
//	}
//	FILE * file = popen("find . -name '*.wmp' 2>/dev/null", "r");
//	if ( ! file ) {
//		cout << "error when executing cmd" << endl;
//		return 1;
//	}
//	int c;
//	string s;
//	while ( (c = fgetc(file)) != EOF ) {
//		s += (char)c;
//	}
//	cout << s;
//	pclose(file);
//	sleep(2);
	
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	start_color();
	
	
	Menu mainMenu{ "Singleplayer", "Multiplayer (on 1 PC)", "Multiplayer over network", "Controls", "Quit" };
	Menu singlePMenu{ "Play", "Difficulty", "Map", "Back" };
	Menu multiPLocalMenu{ "Play", "Map", "Back" };
	Menu multiPNetworkMenu{ "Create game", "Join game", "Back" };
	
	
	WMap singlePmap("examples/basic.wmp");
	WMap multiPLocalMap("examples/basic.wmp");
	WMap multiPNetworkMap("examples/basic.wmp");
	
	Game gm;
	
	while ( true ) {
		// MAIN MENU
		switch ( mainMenu.run() ) {
			case -1:
				// QUIT BY HOTKEY
				endwin();
				return 0;
			case 0:
				// SINGLEPLAYER MENU
				singleP:
				switch ( singlePMenu.run() ) {
					case -1:
						// QUIT BY HOTKEY
						endwin();
						return 0;
					case 0:
						// PLAY
						gm.run(singlePmap);
						break;
					case 1:
						// DIFFICULTY
						break;
					case 2:
						// MAP
						singlePmap.loadMapScreen();
						goto singleP;
					case 3:
						// BACK
						break;
				}
				break;
			case 1:
				// MULTIPLAYER LOCAL MENU
				multiPLocal:
				switch ( multiPLocalMenu.run() ) {
					case -1:
						// QUIT BY HOTKEY
						endwin();
						return 0;
					case 0:
						// PLAY
						gm.run(multiPLocalMap);
						break;
					case 1:
						// MAP
						multiPLocalMap.loadMapScreen();
						goto multiPLocal;
					case 2:
						// BACK
						break;
				}
				break;
			case 2:
				// MULTIPLAYER NETWORK MENU
				multiPNetwork:
				switch ( multiPNetworkMenu.run() ) {
					case -1:
						// QUIT BY HOTKEY
						endwin();
						return 0;
					case 0:
						// CREATE GAME
						break;
					case 1:
						// JOIN GAME
						break;
					case 2:
						//BACK
						break;
				}
				break;
			case 3:
				// CONTROLS
				controlsScreen();
				break;
			case 4:
				// QUIT
				endwin();
				return 0;
		}
	}
	
	endwin();
	
	return 0;
}