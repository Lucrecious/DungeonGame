#include "halfling.h"

Halfling::Halfling() : Enemy(HalflingKind, 15, 20, 100) {
	this->setName("Halfling");
}

/* TODO 
Halfling causes player attacks to have chance to miss
overload recieve attack function?

*/

