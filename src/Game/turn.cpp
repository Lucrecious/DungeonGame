#include <Game/turn.hpp>

Turn::Turn(TurnKind _kind, Vector target) : kind(_kind) {
	this->target = target;
}
