#include <iostream>
#include <cstring>
#include <unistd.h>
#include <ncurses.h>

#include "menu.h"

Menu::Menu(std::initializer_list<const char *> list)
{
	m_items = new const char* [list.size()];
	
	int i = 0;
	auto it = list.begin();
	for ( ; it != list.end() ; i++,++it )
		m_items[i] = *it;
	
	m_itemCnt = i;
}

Menu::~Menu()
{
	delete [] m_items;
}

int Menu::itemCnt() const
{
	return m_itemCnt;
}

void Menu::selectItem(int itemNum) const
{
	clear();
	int maxx = getmaxx(stdscr);
	int maxy = getmaxy(stdscr);
	int yshift = maxy*0.2;
	int shift = yshift-1;
	
	const char frameChar = 'X';
	for ( int i = 0 ; i < maxx ; i++ ) {
		mvaddch(0,i,frameChar);
		mvaddch(maxy-1,i,frameChar);
	}
	for ( int i = 0 ; i < maxy ; i++ ) {
		mvaddch(i,0,frameChar);
		mvaddch(i,maxx-1,frameChar);
	}
	
	
	attron(A_BOLD);
	for ( int i = 0 ; i < m_itemCnt ; i++ ) {
		if ( i == itemNum ) {
			int xcoord = maxx/2-strlen(m_items[i])/2;
			int ycoord = yshift;
			yshift += shift;
			init_pair(1, COLOR_BLUE, COLOR_BLACK);
			attron(COLOR_PAIR(1));
			mvprintw(ycoord, xcoord-2, ">");
			mvprintw(ycoord, xcoord+strlen(m_items[i])+1, "<");
			attron(A_UNDERLINE);
			mvprintw(ycoord, xcoord, m_items[i]);
			attroff(A_UNDERLINE);
			attroff(COLOR_PAIR(1));
		} else {
			mvprintw(yshift, maxx/2-strlen(m_items[i])/2, m_items[i]);
			yshift += shift;
		}
	}
	attroff(A_BOLD);
	
	refresh();
}

int Menu::run() const
{
	nodelay(stdscr,FALSE);
	
	selectItem(0);
	
	int i = 0;
	int c = 0;
	
	while ( c != '\n' && c != ' ' ) {
		c = getch();
		switch ( c ) {
			case KEY_DOWN:
				if ( i < itemCnt()-1 )
					i++;
				selectItem(i);
				break;
			case KEY_UP:
				if ( i > 0 )
					i--;
				selectItem(i);
				break;
			case 's':
				if ( i < itemCnt()-1 )
					i++;
				selectItem(i);
				break;
			case 'w':
				if ( i > 0 )
					i--;
				selectItem(i);
				break;
			case 'j':
				if ( i < itemCnt()-1 )
					i++;
				selectItem(i);
				break;
			case 'k':
				if ( i > 0 )
					i--;
				selectItem(i);
				break;
			case 'q':
				return -1;
				break;
		}
	}
	
	return i;
}

