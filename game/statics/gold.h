#ifndef GOLD_H
#define GOLD_H

#include "../../globals/kind.h"
#include "../staticentity.h"

class Gold : public StaticEntity {
public:
	const Kind goldKind;
	const int value;
	Gold(Kind);
	const int getValueFrom(Kind) const;
};

#endif
