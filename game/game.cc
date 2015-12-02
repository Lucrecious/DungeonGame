#include "game.h"
#include <vector>
#include "characters/shade.h"
#include "characters/human.h"
#include "statics/potion.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

Game::Game() : controller(0), levelNumber(0), level(0),
			   player(0){
	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();
}

Game::~Game() {
	delete this->level;

	if (this->statics) {
		for (unsigned int i = 0; i < this->statics->size(); i++) {
			delete this->statics->at(i);
			(*this->statics)[i] = 0;
		}
	}

	this->statics->clear();
	delete this->statics;
	this->statics = 0;

	if (this->livings) {
		for (unsigned int i = 0; i < this->livings->size(); i++) {
			delete this->livings->at(i);
			(*this->livings)[i] = 0;
		}
	}
	this->livings->clear();
	delete this->livings;
	this->livings = 0;

}

int Game::getStaticAmount() const {
	return this->statics->size();
}

int Game::getLivingAmount() const {
	return this->livings->size();
}

StaticEntity* Game::getStaticAt(int i) const {
	return this->statics->at(i);
}

LivingEntity* Game::getLivingAt(int i) const {
	return this->livings->at(i);
}

GameObject* Game::addObject(Kind kind) {
	GameObject* gobj = 0;

	switch (kind) {
		case VWallKind:
		case HWallKind:
		case FloorKind:
		case DoorKind:
		case PassageKind:
			gobj = new StaticEntity(kind);
			break;

		case RHPotionKind:
		case BAPotionKind:
		case BDPotionKind:
		case PHPotionKind:
		case WAPotionKind:
		case WDPotionKind:
			gobj = new Potion(kind);
			break;

		case HumanKind:
			gobj = new Human();
			break;

		case ShadeKind:
			gobj =  new Shade();
			break;

		default:
			break;
	}

	if (gobj) {
		gobj->setController(this->controller);
		gobj->setGame(this);
		if (gobj->topKind == LivingKind || gobj->topKind == EnemyKind || gobj->topKind == PlayerKind) {
			this->livings->push_back(static_cast<LivingEntity*>(gobj));
		}
		else {
			this->statics->push_back(static_cast<StaticEntity*>(gobj));
		}
	}

	return gobj;
}

void Game::update() {

	sort(this->livings->begin(),
		 this->livings->end(),
		 GameObject::less_than);

	ostringstream flavor("");

	for (int i = 0; i < (int)this->livings->size(); i++) {
		LivingEntity* gobj = this->livings->at(i);
		if (gobj->isDead()) {
			continue;
		}
		Turn turn = gobj->getTurn();
		GameObject* affectedgobj = 0;
		if (this->doTurn(turn, gobj, flavor, affectedgobj)) {
			gobj->turnSucceeded(turn, true);
		}
		else {
			gobj->turnSucceeded(turn, false);
		}
	}
	this->passInformationText();
	this->passFlavorText(flavor.str());
}

void Game::passInformationText() const{
	this->controller->passInformationText(
			this->player->getAtkStat(),
			this->player->getDefStat(),
			this->player->getHP(),
			this->player->getMaxHP(),
			this->player->subKind,
			this->levelNumber);
}

void Game::passFlavorText(string text) const{
	this->controller->passFlavorText(text);
}


bool Game::doTurn(Turn turn, LivingEntity* gobj,
				  ostream& flavor, GameObject*& affected) {
	Vector target = turn.target;
	Vector pos = gobj->getPosition();
	GameObject* tgobj = this->level->get(target + pos);
	affected = tgobj;

	switch (turn.kind) {
		case Move:
			{
			if (!this->level->isFree(pos + target, gobj)) {
				return false;
			}
			this->level->move(pos, pos + target);
			this->controller->notify(
					pos,
					this->level->getKindAt(pos));
			this->controller->notify(
					pos + target,
					gobj->subKind);
			break;
			}
		case Drink:
			{
				if (tgobj && tgobj->subKind == PotionKind) {
					gobj->drink(static_cast<Potion*>(tgobj));
					this->level->remove(target + pos);
					this->controller->notify(
							target + pos,
							this->level->getKindAt(target+pos));
					flavor << "You have drank a " 
						<< tgobj->getName() << endl;
					break;
				}

				if (gobj->topKind == PlayerKind) {
					flavor << "You can't drink that." << endl;
				}

				return false;
			}
		case Attack:
			{
				if (tgobj) {
					cout << "Attempting to attack: " << tgobj->getName() << " -- game.cc" << endl;
				}
				if (tgobj && 
				   (tgobj->topKind == EnemyKind ||
					tgobj->topKind == PlayerKind)) {

					cout << "KIND ATTACKING: " << gobj->topKind << " -- game.cc"  << endl;

					LivingEntity* living =
						static_cast<LivingEntity*>(tgobj);

					int damage = gobj->getAttackDamage(gobj);

					if (gobj->topKind == EnemyKind) {
						flavor << gobj->getName()
							<< " attacks you";
					}
					else {
						flavor << "You attack the "
							<< living->getName();
					}
					
					flavor << " for " << damage << " damage!";

					bool hits = living->receiveAttack(
							gobj, damage);

					flavor << (hits ? " And it hits!" :
									  " And it misses...")
						   << endl;

					if (living->isDead()) {

						this->level->remove(living->getPosition());
						this->controller->notify(
								living->getPosition(),
								this->level->getKindAt(living->getPosition()));
						flavor << "The " << living->getName() << " has been slain!" << endl;
					}

					return hits;;

				}

				if (gobj->topKind == PlayerKind) {
					flavor << "You can't attack that." << endl;
				}

				return false;
			}
		default:
			return false;
	}

	return true;
}

void Game::clearNonPlayerObjects() {
	for (int i = 0; i < (int)this->statics->size(); i++) {
		delete this->statics->at(i);
	}

	for (int i = 0; i < (int)this->livings->size(); i++) {
		if (this->livings->at(i) != this->player) {
			delete this->livings->at(i);
		}
	}

	delete this->statics;
	delete this->livings;

	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();
	if (this->player) {
		this->livings->push_back(this->player);
	}

}

void Game::notifyWholeLevel() {
	Vector v;
	for (int i = 0; i < Global::levelHeight; i++) {
		v.y = i;
		for (int j = 0; j < Global::levelWidth; j++) {
			v.x = j;
			if (this->level->getKindAt(v) != NoneKind) {
				this->controller->notify(v,
					this->level->getKindAt(v));
			}
		}
	}
}

void Game::buildLevel(istream& in) {
	this->levelNumber++;
	this->clearNonPlayerObjects();
	delete this->level;
	this->level = 0;

	this->level = new Level(this);

	ifstream empty("./assets/layout1.txt");
	this->level->init(empty);
	empty.close();

	this->level->load(in);

	this->level->place(
			this->player,
			this->level->getPlayerSpawn());

	this->notifyWholeLevel();
}

void Game::setController(Controller* controller) {
	this->controller = controller;
}

void Game::setPlayer(Kind kind) {
	GameObject* player = this->addObject(kind);
	this->player = static_cast<Player*>(player);
}

Player* Game::getPlayer() const {
	return this->player;
}


