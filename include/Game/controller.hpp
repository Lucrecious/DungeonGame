#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <Game/notification.hpp>
#include <View/textview.hpp>
#include <Game/game.hpp>
#include <Global/kind.hpp>

class Controller : public Notification {
public:
	Controller(std::istream&);
	Game* game;
	View* view;

	Turn getInput() const;

	void notify(Vector, Kind) const;

	void passInformationText(
			int atk, int def, int hp, int maxhp, int gold, std::string race, int level) const;
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
