#include "drow.h"

Drow::Drow() : Player(DrowKind, 25, 15, 150) {
	this->setName("Drow");
}


void Drow::drink(Potion* potion) {
	this->addNewKnownPotion(potion->potionKind);
	switch(potion->potionKind) {
		case BAPotionKind:
		case BDPotionKind:
		case WAPotionKind:
		case WDPotionKind:
		//TODO: amplify potion effects by 1.5
			this->effect = potion->getEffect(this->effect); 
			break;
		
		case RHPotionKind:
			this->setHP(this->getHP() + (10 * 1.5));
			break;
		case PHPotionKind:
			this->setHP(this->getHP() - (10 * 1.5));
			break;
		default:
			break;
	}
}
