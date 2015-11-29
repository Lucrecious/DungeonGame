#include "game.h"
#include <vector>
#include "characters/shade.h"
#include <fstream>
using namespace std;

Game::Game() : controller(0), currentLevel(0) {
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
	// TODO: Basically the entire fucking thing
	if (this->currentLevel == 0) {
		this->currentLevel = new Level(this);
		ifstream f("./assets/layout1.txt");
		this->currentLevel->init(f);
		f.close();
		this->init();
	}
}

void Game::init() {
	Vector v;
	for (int i = 0; i < Global::levelHeight; i++) {
		v.y = i;
		for (int j = 0; j < Global::levelWidth; j++) {
			v.x = j;
			if (this->currentLevel->tiles[i][j]) {
				this->controller->notify(v,
						this->currentLevel->tiles[i][j]->peek()->subKind);
			}
		}
	}
}

void Game::setController(Controller* controller) {
	this->controller = controller;
}










