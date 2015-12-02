#include "human.h"

Human::Human() : Enemy(HumanKind, 20, 20, 140) {
	this->setName("Human");
}
