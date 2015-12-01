#include "gameobject.h"

GameObject::GameObject(Kind top, Kind sub) : topKind(top), subKind(sub), ghost(false) {
	this->position.x = 0;
	this->position.y = 0;
}

void GameObject::setController(Controller* controller) {
	this->controller = controller;
}

void GameObject::setGame(Game* game) {
	this->game = game;
}

void GameObject::setPosition(Vector vector) {
	this->position = vector;
}

void GameObject::setPosition(int x, int y) {
	this->position.x = x;
	this->position.y = y;
}

Vector GameObject::getPosition() const{
	return this->position;
}

bool GameObject::less_than
	(const GameObject* gobj1, const GameObject* gobj2) {
	if (gobj1->topKind == PlayerKind) {
		return true;
	}

	Vector mine = gobj1->getPosition();
	int d1 = mine.y * Global::levelWidth + mine.x;

	Vector other = gobj2->getPosition();
	int d2 = other.y * Global::levelWidth + other.x;

	return d1 < d2;
}





GameObject::~GameObject() { }
