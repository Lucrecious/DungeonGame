#ifndef BOOSTDEF_H
#define BOOSTDEF_H

#include <Game/Statics/neteffect.hpp>

class BoostDef : public NetEffect {
public:
	const int boostDef;
	BoostDef(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
