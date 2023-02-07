#include <ncurses.h>

#include "coord.h"

Coord::Coord(int x, int y)
{
	m_x = x;
	m_y = y;
}

Coord::Coord(const DIRECTION & dir)
{
	switch ( dir ) {
		case RIGHT:
			m_x = 1;
			m_y = 0;
			break;
		case LEFT:
			m_x = -1;
			m_y = 0;
			break;
		case DOWN:
			m_x = 0;
			m_y = 1;
			break;
		case UP:
			m_x = 0;
			m_y = -1;
			break;
	}
}

Coord Coord::operator+(const Coord & rhs) const
{
	return Coord(m_x+rhs.m_x, m_y+rhs.m_y);
}

void Coord::print(char c) const
{
	mvaddch(m_y, m_x, c);
}

void Coord::print(char c, short color) const
{
	attron(COLOR_PAIR(color));
	mvaddch(m_y, m_x, c);
	attroff(COLOR_PAIR(color));
}

void Coord::turnRight()
{
	if ( m_x == 1 && m_y == 0 ) {
		m_x = 0;
		m_y = 1;
	} else if ( m_x == 0 && m_y == 1 ) {
		m_x = -1;
		m_y = 0;
	} else if ( m_x == -1 && m_y == 0 ) {
		m_x = 0;
		m_y = -1;
	} else if ( m_x == 0 && m_y == -1 ) {
		m_x = 1;
		m_y = 0;
	} else
		throw WrongDirection();
}

void Coord::turnLeft()
{
	if ( m_x == 1 && m_y == 0 ) {
		m_x = 0;
		m_y = -1;
	} else if ( m_x == 0 && m_y == 1 ) {
		m_x = 1;
		m_y = 0;
	} else if ( m_x == -1 && m_y == 0 ) {
		m_x = 0;
		m_y = 1;
	} else if ( m_x == 0 && m_y == -1 ) {
		m_x = -1;
		m_y = 0;
	} else
		throw WrongDirection();
}

void Coord::operator=(const DIRECTION & dir)
{
	switch ( dir ) {
		case RIGHT:
			m_x = 1;
			m_y = 0;
			break;
		case LEFT:
			m_x = -1;
			m_y = 0;
			break;
		case DOWN:
			m_x = 0;
			m_y = 1;
			break;
		case UP:
			m_x = 0;
			m_y = -1;
			break;
	}
}

bool operator==(const Coord & coord, const DIRECTION & dir)
{
	switch ( dir ) {
		case RIGHT:
			return coord.m_x == 1 && coord.m_y == 0;
			break;
		case LEFT:
			return coord.m_x == -1 && coord.m_y == 0;
			break;
		case DOWN:
			return coord.m_x == 0 && coord.m_y == 1;
			break;
		case UP:
			return coord.m_x == 0 && coord.m_y == -1;
			break;
		default:
			throw WrongDirection();
	}
}

bool operator!=(const Coord & coord, const DIRECTION & dir)
{
	return ! ( coord == dir );
}

bool operator==(const DIRECTION & dir, const Coord & coord)
{
	return coord == dir;
}

bool operator!=(const DIRECTION & dir, const Coord & coord)
{
	return ! ( coord == dir );
}

