#include "controller.h"
#include "../globals/global.h"
#include <fstream>
#include <string>
using namespace std;

Controller::Controller(istream& input, string _save)
	 : game(0), view(0), in(input), save(_save) { } 


void Controller::passInformationText(
		int atk, int def, int hp, int maxhp, int gold, string race, int level) const {
	this->view->setInformationText(
			atk, def, hp, maxhp, gold, race, level);
}

void Controller::passFlavorText(string text) const{
	string t = "Nothing special this turn.\n";
	if (text != "") {
		t = text;
	}

	this->view->setFlavorText(t);
}

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
	
	string command = this->commandBuffer;

	TurnKind kind = Move;

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

void Controller::main() {
	bool begun = false;
	
	string preGamePrompt =
		"Select a race <s, g, t>, quit(q) or restart(r)";
	string inGamePrompt =
		"What do you want to do?";

	string prompt = preGamePrompt;

	while (true) {
		
		cout << prompt << " ";
		this->in >> this->commandBuffer;
		
		if (this->commandBuffer == "q") {
			break;
		}

		if (this->commandBuffer == "r") {
			begun = false;
			prompt = preGamePrompt;
			continue;
		}


		if (!begun) {
			if (this->commandBuffer == "s" ||
				this->commandBuffer == "g" ||
				this->commandBuffer == "t") {
				this->kill();
				begun = true;
				Kind kind = this->getRaceFromString(this->commandBuffer);
				bool randomized = this->save == ""; 

				this->game = new Game(/*randomized*/);
				this->game->setController(this);
				this->game->setPlayer(kind);

				this->view = new TextView(
						Global::levelWidth,
						Global::levelHeight);

				if (!randomized) {
					this->loader.open(this->save.c_str());
				}

				// Inits the first level
				this->nextLevel();
				this->game->passInformationText();
				prompt = inGamePrompt;
				this->view->display();
			}
			continue;
		}
		
		// the command buffer is avaliable to the player from
		//   get input... So if none of the above commands
		//   are valid, the getInput command gets called
		//   and uses the already stored command in
		//   commandBuffer.

		this->game->update();

		if (this->game->isPlayerDead()) {
			begun = false;
			this->kill();
			prompt = preGamePrompt;
			
			this->printLoseDialogue();

			continue;
		}

		if (this->game->goToNextLevel()) {
			if (this->game->getLevelNumber() == 5) {
				begun = false;
				prompt = preGamePrompt;
				
				int score = this->game->getCurrentScore();
				printWinDialogue(score);
				this->kill();
				continue;
			}
			this->nextLevel();
			this->game->passInformationText();
		}

		this->view->display();
	}

	this->kill();
}

void Controller::printWinDialogue(const int score) const {
	cout << "You made it through alive... Ballin!" << endl;
	cout << "Score: " << score << endl;
}

void Controller::printLoseDialogue() const {
	cout << "You're dead." << endl;
	cout << "Your friends are dead." <<endl;
	cout << "Your family's dead." << endl;
	cout << "Your f**king pets are being skinned alive." << endl;
	cout << "Your mom's a f**king whore." << endl;
	cout << "You suck at life." << endl;
	cout << "The whole world hate's you." << endl;
	cout << "You're going to hell." << endl;
	cout << "Live with it." << endl << endl;
	cout << "Game Over" << endl;
}

void Controller::nextLevel() {
	if (this->loader.is_open()) {
		this->game->buildLevel(this->loader);
	}
	else {
		// here we need the buildLevel that
		//   randomizes
		// this->game->buildLevel();
	}
}

void Controller::kill() {
	delete this->game;
	this->game = NULL;

	delete this->view;
	this->view = NULL;

	
	if (loader.is_open()) {
		loader.close();
	}
	loader.clear();
	
}

Kind Controller::getRaceFromString(string s) {
	if (s == "s") {
		return ShadeKind;
	}
	else if (s == "g") {
		return GoblinKind;
	}else if (s == "t") {
		return TrollKind;
	}
	else {
		return NoneKind;
	}
}







