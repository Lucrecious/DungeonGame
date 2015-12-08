#ifndef DRAGON_H
#define DRAGON_H

#include <Game/enemy.hpp>

class DragonGold;

class Dragon : public Enemy {
public:
	Dragon();
	Turn getTurn();
	void pair(DragonGold*);
	DragonGold* dgold;
};

#endif
