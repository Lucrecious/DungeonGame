#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "notification.h"
#include "../view/textview.h"
#include "game.h"
#include "../globals/kind.h"

class Controller : public Notification {
public:
	Controller(std::istream&, std::string save);
	Game* game;
	View* view;

	Turn getInput() const;
	void notify(Vector, Kind) const;
	void passInformationText(
			int atk, int def, int hp, int maxhp, Kind race, int level) const;
	void main();
private:
	void nextLevel();
	Kind getRaceFromString(std::string);
	std::string commandBuffer;
	std::istream& in;
	std::ifstream loader;
	Vector getDirection(std::string) const;
	std::string save;
	void kill();
};

#endif
