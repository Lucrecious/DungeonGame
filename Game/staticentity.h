#include "gameobject.h"

class StaticEntity : public GameObject {
public:
	virtual StaticEntity(Kind) = 0;
};
