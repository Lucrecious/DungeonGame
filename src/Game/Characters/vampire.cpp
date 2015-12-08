#include <Game/Characters/vampire.hpp>
using namespace std;

Vampire::Vampire() : Player(VampireKind, 25, 25, 50) {
	this->setName("Vampire");
}

void Vampire::turnSucceeded(Turn turn, bool s, GameObject* gobj, ostream& flavor){
	if (turn.kind == Attack && s) {
		if (gobj && gobj->subKind == DwarfKind) {
			this->setHP(this->getHP() - 5);
			flavor << " You're alergic to Dwarfs, you lose 5 HP. ";
		}
		else {
			this->setHP(this->getHP() + 5);
			flavor << " You gained 5 HP from sucking blood. ";
		}
	}
}

void Vampire::setHP(int hp) {
	this->currentHP = hp;
	if (hp < 0) {
		this->currentHP = 0;
	}
}
