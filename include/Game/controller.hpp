#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <Game/notification.hpp>
#include <View/textview.hpp>
#include <Game/game.hpp>
#include <Global/kind.hpp>
#include <Global/information.hpp>

class Controller : public Notification {
public:
	Controller(std::istream&);
	Game* game;
	View* view;

	Turn getInput() const;

	void notify(Vector, Kind) const;

	void passInformation() const;
	void passFlavorText(std::string) const;

	void main();

	void printWinDialogue(const int score) const;
	void printLoseDialogue() const;

private:
	
	void nextLevel();

	Kind getRaceFromString(std::string);

	std::string commandBuffer;
	std::istream& in;

	Vector getDirection(std::string) const;

	void kill();
};

#endif
