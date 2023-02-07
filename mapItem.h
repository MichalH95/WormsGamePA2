#ifndef MAPITEM_H
#define MAPITEM_H

class WormMItemCollision {};
class ScoreUp {};

class MapItem {
public:
	virtual ~MapItem();
	virtual void print() const = 0;
	virtual void action() const = 0;
protected:
	MapItem(int x, int y);
	int m_x;
	int m_y;
};




class EmptyMItem : public MapItem {
public:
	EmptyMItem(int x, int y);
	virtual void print() const;
	virtual void action() const;
};

class NonEmptyMItem : public MapItem {
public:
	NonEmptyMItem(int x, int y, char c);
	virtual void print() const;
	virtual void action() const = 0;
protected:
	const char m_char;
};




class SolidMItem : public NonEmptyMItem {
public:
	SolidMItem(int x, int y);
	virtual void action() const;
};

class YummyMItem : public NonEmptyMItem {
public:
	YummyMItem(int x, int y);
	virtual void print() const;
	virtual void action() const;
};

class WormMItem : public NonEmptyMItem {
public:
	WormMItem(int x, int y);
	virtual void action() const;
};



#endif /* MAPITEM_H */

