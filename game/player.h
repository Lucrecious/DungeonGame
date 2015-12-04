#ifndef PLAYER_H
#define PLAYER_H

#include "livingentity.h"
#include "statics/gold.h"

class Player : public LivingEntity {
public:
	Player(Kind, int, int, int);
	Turn getTurn();

	// only the player to get gold
	void addGold(Gold* gold);
	void addGold(int gold);
	int getGold() const;

	// The player can dodge attacks!
	bool receiveAttack(LivingEntity*, int);

private:
	int goldValue;
};




#endif
