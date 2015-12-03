#ifndef DRAGONGOLD_H
#define DRAGONGOLD_H

#include "gold.h"

class Dragon;

class DragonGold : public Gold {
public:
	DragonGold();
	Dragon* dragon;
	void pair();
	void unghost();
	GameObject* findDragon(Vector&);
};

#endif
