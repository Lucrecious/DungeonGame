#ifndef HALFLING_H
#define HALFLING_H

#include "../enemy.h"

class Halfling : public Enemy {
public:
	Halfling();
	bool receiveAttack(LivingEntity*, int);
};

#endif
