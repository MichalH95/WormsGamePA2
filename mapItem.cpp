#include <ncurses.h>

#include "mapItem.h"

MapItem::~MapItem()
{}

void EmptyMItem::print() const
{}

void EmptyMItem::action() const
{}

MapItem::MapItem(int x, int y)
: m_x(x), m_y(y)
{
}

EmptyMItem::EmptyMItem(int x, int y)
: MapItem(x, y)
{}

NonEmptyMItem::NonEmptyMItem(int x, int y, char c)
: MapItem(x, y), m_char(c)
{}

void NonEmptyMItem::print() const
{
	mvaddch(m_y, m_x, m_char);
}

SolidMItem::SolidMItem(int x, int y)
: NonEmptyMItem(x, y, 'X')
{}

void SolidMItem::action() const
{
	throw WormMItemCollision();
}

YummyMItem::YummyMItem(int x, int y)
: NonEmptyMItem(x, y, 'o')
{}

void YummyMItem::print() const
{
	init_pair(3, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvaddch(m_y, m_x, m_char);
	attroff(COLOR_PAIR(3));
}

void YummyMItem::action() const
{
	throw ScoreUp();
}

WormMItem::WormMItem(int x, int y)
: NonEmptyMItem(x, y, ' ')
{}

void WormMItem::action() const
{
	throw WormMItemCollision();
}

