#ifndef GAME_H
#define GAME_H

#include "wmap.h"
#include "worm.h"

int controlWorm(int c, Worm & w1, Worm & w2, const WMap & map);

class Game {
public:
	Game();
	~Game();
	void run(WMap & map);
private:
	
};

#endif /* GAME_H */