#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <ncurses.h>
#include <cstdlib>
#include <sys/time.h>
#include <bitset>
#include <string>
#include <unistd.h>
#include <memory>

#include "worm.h"
#include "wmap.h"
#include "coord.h"
#include "helper.h"

using namespace std;


WMap::WMap(const char * filename)
{
	if ( ! readFile(filename) ) {
		clearMap();
		defaultMap();
	}
}

WMap::WMap()
{
	defaultMap();
}

WMap::~WMap()
{
}

bool WMap::readFile(const char * filename)
{
	uint32_t width;
	uint32_t height;
	ifstream ifs(filename, ios::in | ios::binary);
	ifs.read((char *)&width, 4);
	ifs.read((char *)&height, 4);
	if ( ! ifs.good() )
		return false;
	m_height = (int)height;
	m_width = (int)width;
	
	m_mapItems.resize( height );
	for ( uint32_t i = 0 ; i < height ; i++ )
		m_mapItems[i].reserve(width);
	
	
	uint32_t bytesPerLine = (width+7)/8;
	bitset<8> bts;
	for ( uint32_t j = 0 ; j < height ; j++ ) {
		for ( uint32_t i = 0 ; i < bytesPerLine ; i++ ) {
			bts = ifs.get();
			for ( int k = 7 ; k >= 0 ; k-- ) {
				if ( bts[k] )
					m_mapItems[j].emplace_back(new SolidMItem(8*i + (-k)+7, j));
				else
					m_mapItems[j].emplace_back(new EmptyMItem(8*i + (-k)+7, j));
			}
		}
	}
	if ( ! ifs.good() ) {
		for ( uint32_t i = 0 ; i < height ; i++ )
			m_mapItems[i].clear();
		
		m_mapItems.clear();
		ifs.close();
		return false;
	}
	ifs.get();
	if ( ! ifs.eof() ) {
		for ( uint32_t i = 0 ; i < height ; i++ )
			m_mapItems[i].clear();
		
		m_mapItems.clear();
		ifs.close();
		return false;
	}
	ifs.clear();
	ifs.close();
	return ifs.good();
}

void WMap::action(const Coord & c) const
{
	m_mapItems[c.m_y][c.m_x]->action();
}

void WMap::clearMap()
{
	for ( auto & v : m_mapItems )
		v.clear();
	m_mapItems.clear();
}

void WMap::defaultMap()
{
	m_width = 80;
	m_height = 23;
	
	m_mapItems.resize( m_height );
	for ( int i = 0 ; i < m_height ; i++ )
		m_mapItems[i].reserve(m_width);
	
	for ( int i = 0 ; i < m_width ; i++ )
		m_mapItems[0].emplace_back(new SolidMItem(i, 0));
	
	for ( int i = 1 ; i < m_height-1 ; i++ ) {
		m_mapItems[i].emplace_back(new SolidMItem(0, i));
		for ( int j = 1 ; j < m_width-1 ; j++ )
			m_mapItems[i].emplace_back(new EmptyMItem(j, i));
		m_mapItems[i].emplace_back(new SolidMItem(m_width-1, i));
	}
	
	for ( int i = 0 ; i < m_width ; i++ )
		m_mapItems[m_height-1].emplace_back(new SolidMItem(i, m_height-1));
}

void WMap::print() const
{
	clear();
	for ( int i = 0 ; i < m_height ; i++ )
		for ( int j = 0 ; j < m_width ; j++ )
			m_mapItems[i][j]->print();
	refresh();
}

void WMap::printItem(const Coord & c) const
{
	m_mapItems[c.m_y][c.m_x]->print();
}

void WMap::setWormMItem(int x, int y)
{
	m_mapItems[y][x] = unique_ptr<WormMItem>(new WormMItem(x, y));
}

void WMap::setWormMItem(const Coord & c)
{
	m_mapItems[c.m_y][c.m_x] = unique_ptr<WormMItem>(new WormMItem(c.m_x, c.m_y));
}

void WMap::setEmptyMItem(int x, int y)
{
	m_mapItems[y][x] = unique_ptr<EmptyMItem>(new EmptyMItem(x, y));
}

void WMap::setEmptyMItem(const Coord & c)
{
	m_mapItems[c.m_y][c.m_x] = unique_ptr<EmptyMItem>(new EmptyMItem(c.m_x, c.m_y));
}

Coord WMap::generateNewYummyPos()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	srand(tv.tv_usec);
	
	int posy = rand() % m_height;
	int posx = rand() % m_width;
	
	while ( dynamic_cast<NonEmptyMItem*>(m_mapItems[posy][posx].get()) ) {
		usleep(2);
		gettimeofday(&tv,NULL);
		srand(tv.tv_usec);
		posy = rand() % m_height;
		posx = rand() % m_width;
	}
	
	m_mapItems[posy][posx] = unique_ptr<YummyMItem>(new YummyMItem(posx, posy));
	m_yummyItems.push_back(Coord(posx, posy));
	
	return Coord(posx, posy);
}

void WMap::deleteYummyItems()
{
	for ( auto & c : m_yummyItems )
		m_mapItems[c.m_y][c.m_x] = unique_ptr<EmptyMItem>(new EmptyMItem(c.m_x, c.m_y));
	
	m_yummyItems.clear();
}

Coord WMap::generateNewWormPos() const
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	srand(tv.tv_usec);
	
	int posy = rand() % m_height;
	int posx = rand() % m_width;
	
	while ( ! checkNewWormPos(Coord(posx, posy)) ) {
		usleep(2);
		gettimeofday(&tv,NULL);
		srand(tv.tv_usec);
		posy = rand() % m_height;
		posx = rand() % m_width;
	}
	
	return Coord(posx, posy);
}

bool WMap::checkNewWormPos(const Coord & c) const
{
	if ( c.m_y - 3 < 0 || c.m_y + 4 > m_height - 1 )
			return false;
	
	for ( int i = 0 ; i < 8 ; i++ )
		if ( dynamic_cast<NonEmptyMItem*>(m_mapItems[ c.m_y - 3 + i ][ c.m_x ].get()) )
			return false;
	
	return true;
}

void WMap::loadMapScreen()
{
	clear();
	
	int maxx = getmaxx(stdscr);
	int maxy = getmaxy(stdscr);
	printFrame();
	
	mvprintw(maxy/2-3, (maxx-24)/2, "Enter map filename:");
	
	refresh();
	
	char filename[100];
	
	echo();
	curs_set(TRUE);
	
	mvgetnstr(maxy/2, (maxx-20)/2, filename, 99);
	
	noecho();
	curs_set(FALSE);
	
	clearMap();
	if ( ! readFile(filename) ) {
		printError("Could not read map.");
		clearMap();
		defaultMap();
	}
}

