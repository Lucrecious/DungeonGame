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

void Vampire::setHP(int hp) {
	this->currentHP = hp;
	if (hp < 0) {
		this->currentHP = 0;
	}
}
