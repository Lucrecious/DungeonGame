#ifndef PLAYER_H
#define PLAYER_H

#include "livingentity.h"
#include "statics/gold.h"

class Player : public LivingEntity {
public:
	Player(Kind, int, int, int);
	Turn getTurn();

	void addGold(Gold* gold);
	int getGold() const;

	bool receiveAttack(LivingEntity*, int);

private:
	int goldValue;
};




#endif
