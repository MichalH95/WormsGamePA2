#include <iostream>
#include <list>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <unistd.h>

#include "worm.h"
#include "coord.h"
#include "wmap.h"
#include "mapItem.h"

Worm::Worm(WMap & map, int playerNum, short color)
: m_direction(DOWN), m_map(map), m_score(0), m_lives(4), m_playerNum(playerNum), m_color(color)
{
	Coord newPos = m_map.generateNewWormPos();
	m_body.push_back(Coord(newPos.m_x, newPos.m_y-3));
	m_body.push_back(Coord(newPos.m_x, newPos.m_y-2));
	m_body.push_back(Coord(newPos.m_x, newPos.m_y-1));
	m_body.push_back(Coord(newPos.m_x, newPos.m_y-0));
}

Worm::~Worm()
{
	
}

void Worm::movePrint()
{
	Coord nextCoord = m_body.back()+m_direction;
	try {
		m_map.action(nextCoord);
	}
	catch ( WormMItemCollision ) {
		blink();
		print(' ');
		removeFromMap();
		m_body.clear();
		m_score -= 5;
		m_lives -= 1;
		if ( m_lives == 0 )
			throw EndOfGame();
		m_direction = DOWN;
		Coord newPos = m_map.generateNewWormPos();
		m_body.push_back(Coord(newPos.m_x, newPos.m_y-3));
		m_body.push_back(Coord(newPos.m_x, newPos.m_y-2));
		m_body.push_back(Coord(newPos.m_x, newPos.m_y-1));
		m_body.push_back(Coord(newPos.m_x, newPos.m_y-0));
		saveToMap();
		print('O');
		return;
	}
	catch ( ScoreUp ) {
		m_score++;
		m_body.push_front(m_body.front());
		m_map.setEmptyMItem(nextCoord.m_x, nextCoord.m_y);
		m_map.printItem(m_map.generateNewYummyPos());
	}
	
	m_body.push_back( nextCoord );
	m_map.setWormMItem( nextCoord );
	m_body.back().print('O', m_color);
	
	m_body.front().print(' ');
	m_map.setEmptyMItem( m_body.front() );
	m_body.pop_front();
}

void Worm::print(const char c) const
{
	attron(COLOR_PAIR(m_color));
	for ( auto & v : m_body )
		v.print(c);
	attroff(COLOR_PAIR(m_color));
}

void Worm::turn(const DIRECTION & dir)
{
	m_direction = dir;
}

void Worm::blink()
{
	for ( int i = 0 ; i < 3 ; i++ ) {
		for ( auto & v : m_body ) {
			v.print(' ');
		}
		refresh();
		usleep(200000);
		for ( auto & v : m_body ) {
			v.print('O', m_color);
		}
		refresh();
		usleep(200000);
	}
}

void Worm::saveToMap()
{
	for ( auto & v : m_body ) {
		m_map.setWormMItem(v.m_x, v.m_y);
	}
}

void Worm::removeFromMap()
{
	for ( auto & v : m_body ) {
		m_map.setEmptyMItem(v.m_x, v.m_y);
	}
}

void Worm::printScore(int offset) const
{
	std::ostringstream os;
	os << "|Player " << m_playerNum << "| SCORE: " << m_score << " LIVES: " << m_lives;
	mvprintw(m_map.m_height, offset, std::string(35, ' ').c_str());
	attron(COLOR_PAIR(m_color));
	mvprintw(m_map.m_height, offset, os.str().c_str() );
	attroff(COLOR_PAIR(m_color));
}

Coord Worm::direction() const
{
	return m_direction;
}

short Worm::color() const
{
	return m_color;
}

int Worm::score() const
{
	return m_score;
}

int Worm::playerNum() const
{
	return m_playerNum;
}

void Worm::readMoves()
{
	
}

