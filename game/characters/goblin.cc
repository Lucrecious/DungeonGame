#include "goblin.h"

Goblin::Goblin() : Player(GoblinKind, 15, 20, 110) {
	this->setName("Goblin");
}

/* TODO
After killing an enemy, goblins gain 5 bonus gold 
automatically

void Goblin::isTurnSucceed(bool turn){

}

*/