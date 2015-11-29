#include "controller.h"
#include "../globals/global.h"
using namespace std;

Controller::Controller(istream& input) : in(input) { } 

Vector Controller::getDirection(string sdir) const {
	char first_dir = sdir[0];
	char sec_dir = sdir[1];

	Vector vec;
	vec.x = 0;
	vec.y = 0;

	if (first_dir == 'n') {
		vec.y = -1;
	}else if (first_dir == 's') {
		vec.y = 1;
	}

	if (first_dir == 'w' || sec_dir == 'w') {
		vec.x = -1;
	}else if (first_dir == 'e' || sec_dir == 'e') {
		vec.x = 1;
	}

	return vec;
}

Turn Controller::getInput() const {
	string command;

	TurnKind kind = Move;

	this->in >> command;
	if (command == "u") {
		kind = Drink;
		this->in >> command;
	}else if (command == "a") {
		kind = Attack;
		this->in >> command;
	}
	
	Vector vec = this->getDirection(command);

	return Turn(kind, vec);

}

void Controller::notify(Vector v, Kind k) const {
	this->view->notify(v, k);
}

void Controller::play() {
	string command;

	this->game = new Game();
	this->game->setController(this);

	this->view = new TextView(Global::levelWidth, Global::levelHeight);

	while (true) {
		this->in >> command;
		
		if (command == "quit") {
			break;
		}

		this->game->update();
		this->view->display();
	}

	delete this->game;
	delete this->view;
}









