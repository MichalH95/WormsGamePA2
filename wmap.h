#ifndef MAP_H
#define MAP_H

#include <vector>
#include <list>
#include <memory>

#include "mapItem.h"
#include "coord.h"

/**
 * @brief "Worms Map" - represents in-game map.
 */
class WMap {
public:
	/**
	 * Loads map from file or loads the default map if the desired map file
	 * can't be read.
	 */
	WMap(const char * filename);
	WMap();
	~WMap();
	void loadMapScreen();
	void print() const;
	void printItem(const Coord & c) const;
	void action(const Coord & c) const;
	void clearMap();
	void deleteYummyItems();
	void setWormMItem(int x, int y);
	void setWormMItem(const Coord & c);
	void setEmptyMItem(int x, int y);
	void setEmptyMItem(const Coord & c);
	Coord generateNewYummyPos();
	Coord generateNewWormPos() const;
	
	int m_height;
	int m_width;
private:
	std::vector< std::vector<std::unique_ptr<MapItem>> > m_mapItems;
	std::list< Coord > m_yummyItems;
	
	bool checkNewWormPos(const Coord & c) const;
	bool readFile(const char * filename);
	void defaultMap();
};

#endif /* MAP_H */