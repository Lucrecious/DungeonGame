#include "game.h"
#include <vector>
#include "characters/shade.h"
using namespace std;

Game::Game() : controller(0) {
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
}

void Game::setController(Controller* controller) {
	this->controller = controller;
}










