#include "vampire.h"

Vampire::Vampire() : Player(VampireKind, 25, 25, 50) {
	this->setName("Vampire");
}

/* TODO 
vampires gain 5 hp with each successful attack, unless 
attacking a dwarf, which results in -5 hp instead

void Vampire::void isTurnSucceed(bool){

}

*/

/* TODO 

Vampire have no maximum hp: We could make the setHP function
virtual and overload it for the vampire, so that the regular
function will take halt at max hp, but the overloaded function
for the vampire class won't

void LivingEntity::setHP(int hp){
	
}

*/

