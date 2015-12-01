#include "potion.h"
#include "boostatk.h"
#include "boostdef.h"
#include "woundatk.h"
#include "wounddef.h"

Potion::Potion(Kind pKind)
	  : StaticEntity(PotionKind), potionKind(pKind) {
}

Effect* Potion::getEffect(Effect* effect) const {
	switch (this->potionKind) {
		case BAPotionKind:
			return new BoostAtk(effect); 
		case WAPotionKind:
			return new WoundAtk(effect);
		case BDPotionKind:
			return new BoostDef(effect);
		case WDPotionKind:
			return new WoundDef(effect);
		case RHPotionKind:
		case PHPotionKind:
		default:
			return 0;
	}
}

