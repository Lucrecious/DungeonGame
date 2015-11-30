#ifndef WOUNDDEF_H
#define WOUNDDEF_H

#include "neteffect.h"

class WoundDef : public NetEffect {
public:
	const int poisonDef;
	WoundDef(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
