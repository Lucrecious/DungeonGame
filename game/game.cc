#include "game.h"
#include <vector>
#include "characters/shade.h"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game() : controller(0), levelNumber(0), level(0) {
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
}

void Game::clearNonPlayerObjects() {
	for (int i = 0; i < (int)this->statics->size(); i++) {
		delete this->statics->at(i);
	}

	LivingEntity* player = 0;
	for (int i = 0; i < (int)this->livings->size(); i++) {
		if (this->livings->at(i) &&
			this->livings->at(i)->topKind == PlayerKind) {
			player = this->livings->at(i);
		}
		else {
			delete this->livings->at(i);
		}
	}

	delete this->statics;
	delete this->livings;

	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();
	if (player) {
		this->livings->push_back(player);
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

	this->notifyWholeLevel();
}

void Game::setController(Controller* controller) {
	this->controller = controller;
}










