#include "rhpotion.h"

RHPotion::RHPotion() : Potion(RHPotionKind) { }

// Health potions work differently
Effect* RHPotion::getEffect(Effect*) const { return 0; }
