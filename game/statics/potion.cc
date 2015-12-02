#include "potion.h"
#include "boostatk.h"
#include "boostdef.h"
#include "woundatk.h"
#include "wounddef.h"

Potion::Potion(Kind pKind)
	  : StaticEntity(PotionKind), potionKind(pKind) {

	switch(this->potionKind) {
		case BAPotionKind:
			this->setName("Attack Boosting Potion");
			break;
		case WAPotionKind:
			this->setName("Attack Wounding Potion");
			break;
		case BDPotionKind:
			this->setName("Defence Boosting Potion");
			break;
		case WDPotionKind:
			this->setName("Defence Wounding Potion");
			break;
		case RHPotionKind:
			this->setName("Health Restoring Potion");
			break;
		case PHPotionKind:
			this->setName("Poison Potion");
			break;
		default:
			this->setName("Unknown Potion");
			break;
	}
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

