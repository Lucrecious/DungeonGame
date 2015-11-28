#ifndef PLAYER_H
#define PLAYER_H

#include "livingentity.h"

class Player : public LivingEntity {
public:
	Player(Kind);
	Turn getTurn();
};




#endif
