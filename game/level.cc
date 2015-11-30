#include "level.h"
#include "staticentity.h"
#include <iostream>
using namespace std;

Level::Level(Game* g) : game(g) {
	for (int i = 0; i < Global::levelHeight; i++) {
		for (int j = 0; j < Global::levelWidth; j++) {
			this->tiles[i][j] = NULL;
		}
	}

	this->spawn.x = 0;
	this->spawn.y = 0;
}

Level::~Level() {
	for (int i = 0; i < Global::levelHeight; i++) {
		for (int j = 0; j < Global::levelWidth; j++) {
			delete this->tiles[i][j];
		}
	}
}

// This is to load the items and such into the level.
void Level::load(istream& in, bool empty) {
	string line;
	
	// We only need to get 25 lines from the stream
	//   so a "for" is suitable
	for (int i = 0; i < Global::levelHeight; i++) {
		getline(in, line);

		// If the file for some reason runs out early, before we hit the
		//   end, it's better to die silently than at a segmentation fault
		if (in.eof()) {
			cerr << "Level is too short" << endl;
			break;
		}
		
		// We need 79 columns from the line, the
		//   rest is too wide. Also, we need to make sure
		//   we don't get a segmentation fault if the
		//   sting is too short. This "for" stops when either the line is too short
		//   or the line too long.
		for (int j = 0;
				i < Global::levelWidth && j < (int)line.size();
				j++) {
			// We run the given function on this position and
			//   character.
			this->charToObject(i, j, line[j], empty);

		}
	}
}


void Level::load(istream& in) {
	this->load(in, false);
}

// This is strictly to only load empty floors, hence the different name from load.
//   these two functions do the exact the same, but on completely different streams.
void Level::init(istream& in) {
	this->load(in, true);
}

bool Level::isFree(Vector v) {
	Stack<GameObject*>* stack = this->tiles[v.y][v.x];
	if (!stack) {
		return true;
	}

	GameObject* gobj = stack->peek();
	cout << "is ghost " << gobj->ghost << " -- in level.cc" << endl;
	cout << "kind " << gobj->subKind << " -- in level.cc" << endl;
	if (gobj->ghost) {
		return true;
	}

	return false;
}

void Level::charToObject(int i, int j, char c, bool empty) {
	if (c == ' ') {
		return;
	}

	Stack<GameObject*>* stack;
	if (this->tiles[i][j] == NULL) {
		stack = new Stack<GameObject*>();
		this->tiles[i][j] = stack;
	}
	else {
		stack = this->tiles[i][j];
	}
	
	GameObject* gobj = NULL;

	if (!empty) {
		switch(c) {
			case Global::VWallSymbol:
			case Global::HWallSymbol:
			case Global::FloorSymbol:
			case Global::PassageSymbol:
			case Global::DoorSymbol:
				break;
			case Global::PlayerSymbol:
				cout << "make player spawn -- in level.c" << endl;
				this->spawn.x = j;
				this->spawn.y = i;
				break;
			default:
				gobj = this->game->addObject(DoorKind);
		}
	}
	else {
		switch(c) {
			case Global::VWallSymbol:
				gobj = this->game->addObject(VWallKind);
				break;
			case Global::HWallSymbol:
				gobj = this->game->addObject(HWallKind);
				break;
			case Global::FloorSymbol:
				gobj = this->game->addObject(FloorKind);
				break;
			case Global::PassageSymbol:
				gobj = this->game->addObject(PassageKind);
				break;
			case Global::DoorSymbol:
				gobj = this->game->addObject(DoorKind);
				break;
			default:
				gobj = NULL;
				break;
		}
	}

	if (gobj) {
		gobj->setPosition(i, j);
		stack->push(gobj);
	}
}

Vector Level::getPlayerSpawn() {
	return this->spawn;
}

void Level::move(Vector from, Vector to) {
	Stack<GameObject*>* stack = this->tiles[from.y][from.x];
	if (stack) {
		GameObject* gobj = stack->pop();
		Stack<GameObject*>* toStack = this->tiles[to.y][to.x];
		if (!toStack) {
			toStack = new Stack<GameObject*>();
			this->tiles[to.y][to.x] = toStack;
		}

		toStack->push(gobj);
		gobj->setPosition(to);
	}
}

// Assumes the given GameObject is not already on the level...
//   this is only meant to be used on the player, it's a very
//   risky function, later I might add a level field to the
//   game objects just to guard this function, it could
//   screw us if you use it accidently somewhere wrong
void Level::place(GameObject* gobj, Vector pos) {
	Stack<GameObject*>* toStack = this->tiles[pos.y][pos.x];
	if (!toStack) {
		toStack = new Stack<GameObject*>();
		this->tiles[pos.y][pos.x] = toStack;
	}

	toStack->push(gobj);
	gobj->setPosition(pos);
	cout << pos.x << " " << pos.y << endl;
}









