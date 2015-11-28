#include "level.h"
#include "staticentity.h"

Level::Level(Game* game) {

	this->game = game;

	for (int i = 0; i < LEVELSIZE; i++) {
		for (int j = 0; j < LEVELSIZE; j++) {
			Stack<GameObject*>* stack = new Stack<GameObject*>();

			this->tiles[i][j] = stack;
			GameObject* gobj;
			if (i == 0 || i == LEVELSIZE - 1) {
				gobj = this->game->addObject(HWallKind);
			}else if (j == 0 || j == LEVELSIZE - 1) {
				gobj = this->game->addObject(VWallKind);
			}else {
				gobj = this->game->addObject(FloorKind);
			}

			gobj->setPosition(i, j);
			stack->push(gobj);
		}
	}
}


Level::~Level() {
	for (int i = 0; i < LEVELSIZE; i++) {
		for (int j = 0; j < LEVELSIZE; j++) {
			delete this->tiles[i][j];
		}
	}
}





