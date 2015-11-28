#ifndef TURN_H
#define TURN_H


#include "../utils/vector.h"
#include "turnkind.h"

struct Turn {
public:
	const TurnKind kind;

	Turn(TurnKind, Vector);

	// Target vector for the potion, attack and move
	Vector target;
};


#endif
