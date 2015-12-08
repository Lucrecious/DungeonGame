#ifndef POTION_H
#define POTION_H

#include <Game/staticentity.hpp>
#include <Game/Statics/effect.hpp>
#include <iostream>

class Potion : public StaticEntity {
public:
	const Kind potionKind;
	Potion(Kind);
	Effect* getEffect(Effect*) const;
};

#endif
