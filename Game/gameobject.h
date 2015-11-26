#include "vector.h"
#include "kind.h"

class Controller;

class GameObject {
public:
	const Kind kind;

	GameObject(Kind);
	void setPosition(Vector);
	void setPosition(int, int);
	Vector getPosition();
	void setController(Controller*);

protected:
	Controller* controller;

private:
	Vector position;
};
