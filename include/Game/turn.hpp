#ifndef TURN_H
#define TURN_H


#include <Utils/vector.hpp>
#include <Game/turnkind.hpp>

struct Turn {
public:
	const TurnKind kind;

	Turn(TurnKind, Vector);

	// Target vector for the potion, attack and move
	Vector target;
};


#endif
