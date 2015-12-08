#ifndef NETEFFECT_H
#define NETEFFECT_H

#include <Game/Statics/effect.hpp>

class NetEffect : public Effect {
public:
	NetEffect(Effect*);
	virtual ~NetEffect();
	int getAtkNet();
	int getDefNet();
private:
	Effect* effect;
};

#endif
