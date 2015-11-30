#ifndef PHPOTION_H
#define PHPOTION_H

#include "potion.h"

class PHPotion : public Potion {
public:
	PHPotion();
	Effect* getEffect(Effect*) const;
};

#endif
