#include <Game/controller.hpp>
#include <Global/global.hpp>
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
		"Select a race [ /s/hade, /g/oblin, /t/roll, /v/ampire, /d/row ], /q/uit or /r/estart ";
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
				this->commandBuffer == "t" ||
				this->commandBuffer == "d" ||
				this->commandBuffer == "v") {
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

				this->nextLevel();
				this->game->passInformationText();
				this->game->passFlavorText("");
				prompt = inGamePrompt;
				this->view->display();
			}
			continue;
		}
		
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
	cout << "Game Over" << endl;
}

void Controller::nextLevel() {
	if (this->loader.is_open()) {
		this->game->buildLevel(this->loader);
	}
	else {
		this->game->buildRandomLevel();
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
	}
	else if (s == "t") {
		return TrollKind;
	}
	else if (s == "v") {
		return VampireKind;
	}
	else if (s == "d") {
		return DrowKind;
	}
	else {
		return NoneKind;
	}
}







