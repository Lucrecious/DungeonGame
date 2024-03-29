#include <Game/level.hpp>
#include <Game/game.hpp>
#include <iostream>
#include <Game/gameobject.hpp>
#include <Game/Statics/dragongold.hpp>
#include <Game/Characters/dragon.hpp>
#include <sstream>
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
	if (stack && stack->peek()) {
		return stack->peek()->subKind;
	}

	return NoneKind;
}

void Level::load(istream& in, bool empty) {
	string line;
	
	for (int i = 0; i < Global::levelHeight; i++) {
		getline(in, line);

		if (in.eof()) {
			cerr << "Level is too short" << endl;
			break;
		}
		
		for (int j = 0;
				i < Global::levelWidth && j < (int)line.size();
				j++) {
			this->charToObject(i, j, line[j], empty);

		}
	}
}

void Level::randomize() {
	int playerChamber = this->getRandomChamber();
	this->spawn = this->getRandomFloorLocation(playerChamber);

	int stairsChamber = playerChamber;
	while (stairsChamber == playerChamber) {
		stairsChamber = this->getRandomChamber();
	}

	this->stairs = this->game->addObject(StairsKind);
	this->place(stairs, this->getRandomFloorLocation(stairsChamber));

	Kind potions[6] = { RHPotionKind, PHPotionKind,
						BAPotionKind, WAPotionKind,
						BDPotionKind, WDPotionKind};
	int potionProbs[6] = { 1, 1, 1, 1, 1, 1 };
	vector<Kind> potionDist = Global::constructProbabilityDist(potions, potionProbs, 6);

	for (int i = 0; i < Global::maxPotions; i++) {
		Kind kind = Global::getRandomKindFrom(potionDist);
		this->addKindInRandomLocation(kind);
	}

	Kind golds[3] = { GoldSmallKind, GoldNormalKind, GoldDragonKind };
	int goldProbs[3] = { 2, 5, 1 };
	vector<Kind> goldDist = Global::constructProbabilityDist(golds, goldProbs, 3);

	for (int i = 0; i < Global::maxGolds; i++) {
		Kind kind = Global::getRandomKindFrom(goldDist);
		this->addKindInRandomLocation(kind);
	}

	Kind enemies[6] = { HumanKind, DwarfKind, HalflingKind, ElfKind, OrcKind, MerchantKind };
	int enemyProbs[6] = { 4, 3, 5, 2, 2, 2 };
	vector<Kind> enemyDist = Global::constructProbabilityDist(enemies, enemyProbs, 6);

	for (int i = 0; i < Global::maxEnemies; i++) {
		Kind kind = Global::getRandomKindFrom(enemyDist);
		this->addKindInRandomLocation(kind);
	}
}

Vector Level::getRandomFloorLocation(int chamber) const {
	GameObject* posObj = 0;
	
	while (!posObj ||  posObj->subKind != FloorKind) {
		int randomLoc = Global::irand(0, this->chambers[chamber].size() - 1);
		posObj = this->get(this->chambers[chamber].at(randomLoc));
	}

	return posObj->getPosition();
}

int Level::getRandomChamber() const {
	int chamber = Global::irand(0, Global::maxChambers - 1);

	return chamber;
}

void Level::addKindInRandomLocation(Kind kind) {
	int chamber = this->getRandomChamber();
	Vector placement = this->getRandomFloorLocation(chamber);

	GameObject* gobj = this->game->addObject(kind);
	this->place(gobj, placement);
}

void Level::load(istream& in) {
	this->load(in, false);
}

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
		return true; 
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
			case Global::DwarfSymbol:
				gobj = this->game->addObject(DwarfKind);
				break;
			case Global::ElfSymbol:
				gobj = this->game->addObject(ElfKind);
				break;
			case Global::OrcSymbol:
				gobj = this->game->addObject(OrcKind);
				break;
			case Global::MerchantSymbol:
				gobj = this->game->addObject(MerchantKind);
				break;
			case Global::HalflingSymbol:
				gobj = this->game->addObject(HalflingKind);
				break;
			case Global::DragonSymbol:
				gobj = this->game->addObject(DragonKind);
				break;

			case Global::StairsSymbol:
				gobj = this->game->addObject(StairsKind);
				this->stairs = gobj;
				break;

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

			case Global::Chamber1Symbol:
			case Global::Chamber2Symbol:
			case Global::Chamber3Symbol:
			case Global::Chamber4Symbol:
			case Global::Chamber5Symbol:
				{
					gobj = this->game->addObject(FloorKind);
					int num;
					stringstream convert;
					convert << c;
					convert >> num;
					Vector v;
					v.x = j;
					v.y = i;
					this->chambers[num].push_back(v);
					break;
				}
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
