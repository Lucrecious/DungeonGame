#ifndef BAPOTION_H
#define BAPOTION_H

#include "potion.h"

class BAPotion : public Potion {
public:
	BAPotion();
	Effect* getEffect(Effect*) const;
};

#endif
