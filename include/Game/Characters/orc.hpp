#ifndef ORC_H
#define ORC_H

#include <Game/enemy.hpp>

class Orc : public Enemy {
public:
	Orc();
	int getAttackDamage(LivingEntity*) const;
};

#endif
