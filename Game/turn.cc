#include "turn.h"

Turn::Turn(TurnKind _kind, Vector target) : kind(_kind) {
	this->target = target;
}
