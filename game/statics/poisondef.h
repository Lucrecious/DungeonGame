#ifndef POISONDEF_H
#define POISONDEF_H

#include "neteffect.h"

class PoisonDef : public NetEffect {
public:
	const int poisonDef;
	PoisonDef(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
