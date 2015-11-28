#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "vector.h"
#include "kind.h"
#include "controller.h"

class Game;

class GameObject {
public:
	const Kind topKind;
	const Kind subKind;
	bool ghost;

	GameObject(Kind, Kind);
	void setPosition(Vector);
	void setPosition(int, int);
	Vector getPosition() const;
	void setController(Controller*);
	void setGame(Game*);

protected:
	Controller* controller;
	Game* game;

private:
	Vector position;
};



#endif
