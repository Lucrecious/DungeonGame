#include "phpotion.h"

PHPotion::PHPotion() : Potion(PHPotionKind) { }

Effect* PHPotion::getEffect(Effect* effect) const { return 0; }
