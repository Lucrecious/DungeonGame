#include <Game/Characters/goblin.hpp>
#include <iostream>
using namespace std;

Goblin::Goblin() : Player(GoblinKind, 15, 20, 110) {
	this->setName("Goblin");
}

void Goblin::turnSucceeded(Turn turn, bool s,
						   GameObject* gobj, ostream& flavor) {
	if (turn.kind == Attack && s) {
		if (gobj && gobj->topKind == EnemyKind) {
			LivingEntity* le = static_cast<LivingEntity*>(gobj);
			if (le->isDead()) {
				flavor << " You stole 5 gold from the corpse of the " << le->getName() << ". ";
				this->addGold(5);
			}
		}
	}
}
