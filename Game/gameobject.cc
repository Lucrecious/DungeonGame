#include "gameobject.h"

GameObject::GameObject(Kind _kind) : kind(_kind), ghost(false) {
	this->position.x = 0;
	this->position.y = 0;
}

void GameObject::setController(Controller* controller) {
	this->controller = controller;
}

void GameObject::setPosition(Vector vector) {
	// TODO: implement
}

void GameObject::setPosition(int x, int y) {
	// TODO: implement
}

Vector GameObject::getPosition() const{
	return this->position;
}
