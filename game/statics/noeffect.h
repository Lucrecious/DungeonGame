#ifndef NOEFFECT_H
#define NOEFFECT_H

#include "effect.h"

class NoEffect : public Effect {
public:
	int getAtkNet();
	int getDefNet();
};

#endif
