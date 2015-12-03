#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"

class DragonGold;

class Dragon : public Enemy {
public:
	Dragon();
	Turn getTurn();
	void pair(DragonGold*);
	DragonGold* gold;
	void turnSucceeded(Turn, bool);
};

#endif
