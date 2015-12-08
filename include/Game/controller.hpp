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
	Controller(std::istream&, std::string save);
	Game* game;
	View* view;

	// Returns a turn given the input the player is typing
	//   it uses the commandBuffer field to keep track of what
	//   is being input. This way the player can handle itself without
	//   understanding the string inputs.
	Turn getInput() const;

	// notitifies the view to change the thing at position of the given Vector
	//   to the given Kind
	void notify(Vector, Kind) const;

	// This passes the information along to the view, from the game
	//   So the stats, level, race and gold for viewing
	void passInformationText(
			int atk, int def, int hp, int maxhp, int gold, std::string race, int level) const;

	// This passes the flavor text to the view, from teh game.
	//   This just informs the player of what is going on
	void passFlavorText(std::string) const;

	// The main function, where the game is played
	void main();

	// What we print when the player wins 
	void printWinDialogue(const int score) const;

	// What we print when the player loses
	void printLoseDialogue() const;
private:
	
	// Makes the game change level, either make the game
	//   read from a file, or generate a level randomly 
	void nextLevel();

	// Converts a string to a race type so the game
	//   can spawn the correct player object
	Kind getRaceFromString(std::string);

	// This holds all the commands the player inputs
	std::string commandBuffer;

	// This is the in stream for the game, where the input
	//   comes from
	std::istream& in;

	// This is where a file to a bunch of levels would go
	//   if the user specifies a valid file path
	std::ifstream loader;

	// gets the direction the user is specifying given a string
	Vector getDirection(std::string) const;

	// This is the file path being used. If it's empty
	//   the game generates random levels
	std::string save;

	// Destroys the Game and View object and makes sure to leave
	//   no string attached (hence the name kill). It's very abrubt
	//   and pushes the user back either to the beginning of the
	//   game or leaves.
	void kill();
};

#endif
