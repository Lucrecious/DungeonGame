#ifndef RHPOTION_H
#define RHPOTION_H

#include "potion.h"

class RHPotion : public Potion { 
	RHPotion();
	Effect* getEffect(Effect*) const;
};

#endif
