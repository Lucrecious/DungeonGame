#include "level.h"
#include <iostream>
#include "gameobject.h"
#include "statics/dragongold.h"
#include "characters/dragon.h"

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

Stack<GameObject*>* Level::getStackAt(Vector target) const {
	return this->tiles[target.y][target.x];
}

Kind Level::getKindAt(Vector target) const {
	Stack<GameObject*>* stack = this->getStackAt(target);
	if (stack) {
		return stack->peek()->subKind;
	}
	return NoneKind;
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

bool Level::isFree(Vector v, GameObject* incoming) const {
	Stack<GameObject*>* stack = this->tiles[v.y][v.x];
	if (!stack) {
		return false;
	}

	GameObject* gobj = stack->peek();
	if (gobj->ghost ||
	    (gobj->subKind == DoorKind &&
		 incoming->topKind == PlayerKind)) {
		return true;
	}
	
	if (incoming->topKind == PlayerKind &&
		gobj->subKind == GoldKind) {
		Gold* gold = static_cast<Gold*>(gobj);
		if (gold->goldKind == GoldDragonKind) {
			DragonGold* dgold = static_cast<DragonGold*>(gold);
			if (dgold->dragon->isDead()){
				return true;
			}
		}
	}

	if (gobj->subKind == StairsKind &&
		incoming->topKind == PlayerKind) {
		Vector diff = gobj->getPosition() - incoming->getPosition();
		return diff.x == 1 && diff.y == 0;
	}

	return false;
}

GameObject* Level::get(Vector target) const {
	Stack<GameObject*>* stack = this->tiles[target.y][target.x];
	if (stack) {
		return stack->peek();
	}

	return 0;
}

void Level::remove(Vector target) {
	Stack<GameObject*>* stack = this->tiles[target.y][target.x];
	if (stack) {
		stack->pop();
	}
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

			// Potions!
			case Global::RHPotionSymbol:
				gobj = this->game->addObject(RHPotionKind);
				break;
			case Global::BAPotionSymbol:
				gobj = this->game->addObject(BAPotionKind);
				break;
			case Global::BDPotionSymbol:
				gobj = this->game->addObject(BDPotionKind);
				break;
			case Global::PHPotionSymbol:
				gobj = this->game->addObject(PHPotionKind);
				break;
			case Global::WAPotionSymbol:
				gobj = this->game->addObject(WAPotionKind);
				break;
			case Global::WDPotionSymbol:
				gobj = this->game->addObject(WDPotionKind);
				break;

			// Gold!
			case Global::GoldSmallSymbol:
				gobj = this->game->addObject(GoldSmallKind);
				break;
			case Global::GoldNormalSymbol:
				gobj = this->game->addObject(GoldNormalKind);
				break;
			case Global::GoldMerchantSymbol:
				gobj = this->game->addObject(GoldMerchantKind);
				break;
			case Global::GoldDragonSymbol:
				gobj = this->game->addObject(GoldDragonKind);
				break;

			case Global::HumanSymbol:
				gobj = this->game->addObject(HumanKind);
				break;
			case Global::DragonSymbol:
				gobj = this->game->addObject(DragonKind);
				break;

			case Global::StairsSymbol:
				gobj = this->game->addObject(StairsKind);
				this->stairs = gobj;
				break;

			// Player!
			case Global::PlayerSymbol:
				this->spawn.x = j;
				this->spawn.y = i;
				break;

			default:
				gobj = this->game->addObject(DoorKind);
				break;
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
		gobj->setPosition(j, i);
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
}

GameObject* Level::getStairs() const {
	return this->stairs;
}







