#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "notification.h"
#include "../view/textview.h"
#include "game.h"

class Controller : public Notification {
public:
	Controller(std::istream&);
	Game* game;
	View* view;

	Turn getInput() const;
	void notify(Vector, Kind) const;
	void play();
private:
	std::istream& in;
	Vector getDirection(std::string) const;
};

#endif
