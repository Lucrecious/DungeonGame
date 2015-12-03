#include "gameobject.h"
#include <string>
using namespace std;

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

void GameObject::setName(string name) {
	this->name = name;
}

string GameObject::getName() const{
	return this->name;
}

bool GameObject::less_than
	(const GameObject* gobj1, const GameObject* gobj2) {
	if (gobj1->topKind == PlayerKind) {
		return true;
	}

	if (gobj2->topKind == PlayerKind) {
		return false;
	}

	Vector mine = gobj1->getPosition();
	int d1 = mine.y * Global::levelWidth + mine.x;

	Vector other = gobj2->getPosition();
	int d2 = other.y * Global::levelWidth + other.x;

	return d1 < d2;
}





GameObject::~GameObject() { }
