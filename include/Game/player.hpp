#ifndef PLAYER_H
#define PLAYER_H

#include <Game/livingentity.hpp>
#include <Game/Statics/gold.hpp>

class Player : public LivingEntity {
public:
	Player(Kind, int, int, int);
	Turn getTurn();

	void addGold(Gold* gold);
	void addGold(int gold);
	int getGold() const;

	bool receiveAttack(LivingEntity*, int);

private:
	int goldValue;
};




#endif
