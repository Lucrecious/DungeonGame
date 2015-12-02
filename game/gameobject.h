#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "../utils/vector.h"
#include "../globals/kind.h"
#include "controller.h"
#include <string>

class Game;

class GameObject {
public:
	const Kind topKind;
	const Kind subKind;
	bool ghost;

	GameObject(Kind, Kind);
	virtual ~GameObject() = 0;

	void setPosition(Vector);
	void setPosition(int, int);
	Vector getPosition() const;
	void setController(Controller*);
	void setGame(Game*);

	static bool less_than(const GameObject* gobj1, const GameObject* gobj2);

	void setName(std::string);
	std::string getName() const;
protected:
	Controller* controller;
	Game* game;

private:
	Vector position;
	std::string name;
};

struct gameobject_less_than {
};

#endif
