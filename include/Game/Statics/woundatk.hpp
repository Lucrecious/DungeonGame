#ifndef WOUNDATK_H
#define WOUNDATK_H

#include <Game/Statics/neteffect.hpp>

class WoundAtk : public NetEffect {
public:
	const int poisonAtk;
	WoundAtk(Effect*);
	int getAtkNet();
	int getDefNet();
};

#endif
