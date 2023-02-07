#ifndef COORD_H
#define COORD_H

class WrongDirection {};

enum DIRECTION { RIGHT=0, LEFT, DOWN, UP };

struct Coord {
	int m_x;
	int m_y;
	
	Coord(int x, int y);
	Coord(const DIRECTION & dir);
	Coord operator+(const Coord & rhs) const;
	void print(char c) const;
	void print(char c, short color) const;
	void turnRight();
	void turnLeft();
	void operator=(const DIRECTION & dir);
};

bool operator==(const Coord & coord, const DIRECTION & dir);
bool operator!=(const Coord & coord, const DIRECTION & dir);
bool operator==(const DIRECTION & dir, const Coord & coord);
bool operator!=(const DIRECTION & dir, const Coord & coord);

#endif /* COORD_H */