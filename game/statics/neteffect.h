#ifndef NETEFFECT_H
#define NETEFFECT_H

#include "effect.h"

class NetEffect : public Effect {
public:
	NetEffect(Effect*);
	~NetEffect();
	int getAtkNet();
	int getDefNet();
private:
	Effect* effect;
};

#endif
