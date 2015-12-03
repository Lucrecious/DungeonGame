#ifndef MERCHANT_H
#define MERCHANT_H

#include "../enemy.h"

class Merchant : public Enemy {
public:
	Merchant();
	bool receiveAttack(LivingEntity*, int);
	Turn getTurn();
	void drop();
};

#endif


