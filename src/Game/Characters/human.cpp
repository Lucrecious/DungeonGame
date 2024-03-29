#include <Game/Characters/human.hpp>
#include <Game/Statics/gold.hpp>
#include <Game/game.hpp>

Human::Human() : Enemy(HumanKind, 20, 20, 140) {
	this->setName("Human");
}

void Human::drop() {
	GameObject* gold1 = this->game->addObject(GoldNormalKind);
	GameObject* gold2 = this->game->addObject(GoldNormalKind);

	this->game->getLevel()->place(gold1, this->getPosition());
	this->game->getLevel()->place(gold2, this->getPosition());
}
