#ifndef WOUNDDEF_H
#define WOUNDDEF_H

#include <Game/Statics/neteffect.hpp>

class WoundDef : public NetEffect {
public:
	const int poisonDef;
	WoundDef(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
