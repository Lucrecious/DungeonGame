#ifndef POISONATK_H
#define POISONATK_H

#include "neteffect.h"

class PoisonAtk : NetEffect {
	const int poisonAtk;
	PoisonAtk(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
