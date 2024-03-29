#include <Game/controller.hpp>
#include <Global/global.hpp>
#include <Global/information.hpp>
#include <fstream>
#include <string>
using namespace std;

Controller::Controller(istream& input)
	 : game(0), view(0), in(input) { } 


void Controller::passInformation() const {
	Information info = Global::makeInfoFromPlayer(this->game->getPlayer(), this->game);
	this->view->setInformationText(info);
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
	Vector vec = { 0, 0 };

	if (command == "u") {
		kind = Drink;
		this->in >> command;
	}else if (command == "a") {
		kind = Attack;
		this->in >> command;
	}else if (command == "h") {
		kind = Heal;
	}
	
	if (kind != Heal) {
		vec = this->getDirection(command);
	}

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

				this->game = new Game();
				this->game->setController(this);
				this->game->setPlayer(kind);

				this->view = new TextView(
						Global::levelWidth,
						Global::levelHeight);

				this->game->buildRandomLevel();
				this->passInformation();
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

			this->game->buildRandomLevel();
			this->passInformation();
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


void Controller::kill() {
	delete this->game;
	this->game = NULL;

	delete this->view;
	this->view = NULL;
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







