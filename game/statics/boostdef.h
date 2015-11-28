#ifndef BOOSTDEF_H
#define BOOSTDEF_H

#include "neteffect.h"

class BoostDef : public NetEffect {
public:
	const int boostDef;
	BoostDef(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
