#include "game.h"
#include <vector>
#include "characters/shade.h"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game() : controller(0), levelNumber(0), level(0),
			   player(0){
	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();
}

Game::~Game() {
	for (unsigned int i = 0; i < this->statics->size(); i++) {
		delete this->statics->at(i);
	}
	delete this->statics;

	for (unsigned int i = 0; i < this->livings->size(); i++) {
		delete this->livings->at(i);
	}
	delete this->livings;

	delete level;

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
	GameObject* gobj;

	switch (kind) {
		case VWallKind:
		case HWallKind:
		case FloorKind:
		case DoorKind:
		case PassageKind:
			gobj = new StaticEntity(kind);
			break;

		case ShadeKind:
			gobj =  new Shade();
			break;
		default:
			break;
	}

	if (gobj) {
		gobj->setController(this->controller);
		if (gobj->topKind == LivingKind) {
			this->livings->push_back(static_cast<LivingEntity*>(gobj));
		}
		else {
			this->statics->push_back(static_cast<StaticEntity*>(gobj));
		}
	}

	return gobj;
}

void Game::update() {
	for (int i = 0; i < (int)this->livings->size(); i++) {
		LivingEntity* gobj = this->livings->at(i);
		Turn turn = gobj->getTurn();
		if (this->doTurn(turn, gobj)) {
			gobj->turnSucceeded(turn, true);
		}
		else {
			gobj->turnSucceeded(turn, false);
		}
	}
}

bool Game::doTurn(Turn turn, GameObject* gobj) {
	switch (turn.kind) {
		case Move:
			{
			Vector target = turn.target;
			Vector pos = gobj->getPosition();

			if (!this->level->isFree(pos + target)) {
				return false;
			}
			cout << "Player position " << pos.x << " " << pos.y << " -- in game.cc" << endl;
			this->level->move(pos, pos + target);
			this->controller->notify(
					pos,
					this->level->tiles[pos.y][pos.x]->peek()->subKind);
			this->controller->notify(
					pos + target,
					gobj->subKind);
			break;
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
			if (this->level->tiles[i][j]) {
				this->controller->notify(v,
					this->level->tiles[i][j]->peek()->subKind);
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


