#ifndef WORM_H
#define WORM_H

#include <list>
#include <queue>

#include "coord.h"
#include "wmap.h"

class EndOfGame {};

class Worm {
public:
	Worm(WMap & map, int playerNum, short color);
	~Worm();
	void movePrint();
	void print(const char c) const;
	void turn(const DIRECTION & dir);
	void blink();
	void saveToMap();
	void removeFromMap();
	void printScore(int offset) const;
	void readMoves();
	
	Coord direction() const;
	short color() const;
	int score() const;
	int playerNum() const;
	
private:
	std::list<Coord> m_body;
	Coord m_direction;
	WMap & m_map;
	int m_score;
	int m_lives;
	int m_playerNum;
	short m_color;
	std::queue<int> m_moves;
};

#endif /* WORM_H */