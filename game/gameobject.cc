#include "gameobject.h"

GameObject::GameObject(Kind top, Kind sub) : topKind(top), subKind(sub), ghost(false) {
	this->position.x = 0;
	this->position.y = 0;
}

void GameObject::setController(Controller* controller) {
	this->controller = controller;
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

GameObject::~GameObject() { }
