#include <Game/Characters/troll.hpp>
using namespace std;

Troll::Troll() : Player(TrollKind, 25, 15, 120) {
	this->setName("Troll");
}


void Troll::turnSucceeded(Turn, bool, GameObject*, ostream& flavor) {
	this->setHP(this->getHP() + 5);
	flavor << " You gain 5 HP from just being a troll! ";
}
