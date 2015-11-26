#include "gameobject.h"

GameObject::GameObject(Kind _kind) : kind(_kind) {
	this->position.x = 0;
	this->position.y = 0;
}

void GameObject::setController(Controller* controller) {
	this->controller = controller;
}

void GameObject::setPosition(Vector vector) {

}

void GameObject::setPosition(int x, int y) {
}

Vector GameObject::getPosition() {
	return this->position;
}
