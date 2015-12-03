#include "goblin.h"
#include <iostream>
using namespace std;

Goblin::Goblin() : Player(GoblinKind, 200, 20, 110) {
	this->setName("Goblin");
}

void Goblin::turnSucceeded(Turn turn, bool s, GameObject* gobj) {
	cout << "in turnsucceeded goblin --goblin.cc" << endl;
	if (turn.kind == Attack && s) {
		if (gobj && gobj->topKind == EnemyKind) {
			LivingEntity* le = static_cast<LivingEntity*>(gobj);
			if (le->isDead()) {
				// Goblin steals 5 gold
				this->addGold(5);
			}
		}
	}
}
