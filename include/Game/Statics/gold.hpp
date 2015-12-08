#ifndef GOLD_H
#define GOLD_H

#include <Global/kind.hpp>
#include <Game/staticentity.hpp>

class Gold : public StaticEntity {
public:
	const Kind goldKind;
	const int value;
	Gold(Kind);
	const int getValueFrom(Kind) const;
};

#endif
