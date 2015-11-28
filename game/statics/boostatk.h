#ifndef BOOSTATK_H
#define BOOSTATK_H

#include "neteffect.h"

class BoostAtk : public NetEffect {
public:
	const int atkBoost;
	BoostAtk(Effect* effect);
	int getAtkNet();
	int getDefNet();
};

#endif
