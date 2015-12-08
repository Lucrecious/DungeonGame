#ifndef HALFLING_H
#define HALFLING_H

#include <Game/enemy.hpp>

class Halfling : public Enemy {
public:
	Halfling();
	bool receiveAttack(LivingEntity*, int);
};

#endif
