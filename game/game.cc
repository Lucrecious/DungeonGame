#include "game.h"
#include <vector>
#include "characters/shade.h"
#include "characters/human.h"
#include "characters/dwarf.h"
#include "characters/dragon.h"
#include "characters/elf.h"
#include "characters/orc.h"
#include "characters/merchant.h"
#include "characters/halfling.h"
#include "characters/goblin.h"
#include "characters/troll.h"
#include "characters/vampire.h"
#include "characters/drow.h"
#include "statics/dragongold.h"
#include "statics/potion.h"
#include "statics/gold.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

Game::Game() : controller(0), levelNumber(0), level(0),
			   player(0), merchantsAttack(false) {
	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();
}

// Kills all the allocated memory in game that game owns
Game::~Game() {
	delete this->level;

	if (this->statics) {
		for (unsigned int i = 0; i < this->statics->size(); i++) {
			delete this->statics->at(i);
			(*this->statics)[i] = 0;
		}
	}

	this->statics->clear();
	delete this->statics;
	this->statics = 0;

	if (this->livings) {
		for (unsigned int i = 0; i < this->livings->size(); i++) {
			delete this->livings->at(i);
			(*this->livings)[i] = 0;
		}
	}
	this->livings->clear();
	delete this->livings;
	this->livings = 0;

}

int Game::getStaticAmount() const {
	return this->statics->size();
}

int Game::getLivingAmount() const {
	return this->livings->size();
}

StaticEntity* Game::getStaticAt(int i) const {
	return this->statics->at(i);
}

LivingEntity* Game::getLivingAt(int i) const {
	return this->livings->at(i);
}

GameObject* Game::addObject(Kind kind) {
	GameObject* gobj = 0;

	// Adds an object given a kind at O(1)
	switch (kind) {
		case VWallKind:
		case HWallKind:
		case FloorKind:
		case DoorKind:
		case PassageKind:
		case StairsKind:
			gobj = new StaticEntity(kind);
			break;

		case RHPotionKind:
		case BAPotionKind:
		case BDPotionKind:
		case PHPotionKind:
		case WAPotionKind:
		case WDPotionKind:
			gobj = new Potion(kind);
			break;

		case GoldSmallKind:
		case GoldNormalKind:
		case GoldMerchantKind:
			gobj = new Gold(kind);
			break;
		case GoldDragonKind:
			gobj = new DragonGold();
			break;

		case HumanKind:
			gobj = new Human();
			break;
		case DwarfKind:
			gobj = new Dwarf();
			break;
		case ElfKind:
			gobj = new Elf();
			break;
		case OrcKind:
			gobj = new Orc();
			break;
		case MerchantKind:
			gobj = new Merchant();
			break;
		case HalflingKind:
			gobj = new Halfling();
			break;

		case DragonKind:
			gobj = new Dragon();
			break;

		case GoblinKind:
			gobj = new Goblin();
			break;
		case TrollKind:
			gobj = new Troll();
			break;
		case VampireKind:
			gobj = new Vampire();
			break;
			case DrowKind:
			gobj = new Drow();
			break;
		case ShadeKind:
			gobj =  new Shade();
			break;

		default:
			break;
	}

	// if an object has been made we need to add it and initialize it
	if (gobj) {
		gobj->setController(this->controller);
		gobj->setGame(this);
		if (gobj->topKind == LivingKind || gobj->topKind == EnemyKind || gobj->topKind == PlayerKind) {
			this->livings->push_back(static_cast<LivingEntity*>(gobj));
		}
		else {
			this->statics->push_back(static_cast<StaticEntity*>(gobj));
		}
	}

	return gobj;
}

void Game::update() {
	
	// We need to make sure the player goes first and that the enemies are updated
	//   row by row isntead of time of creation
	sort(this->livings->begin(),
		 this->livings->end(),
		 GameObject::less_than);

	ostringstream flavor("");

	// Iterate through all livings to get their turn
	for (int i = 0; i < (int)this->livings->size(); i++) {
		LivingEntity* gobj = this->livings->at(i);

		// If a living is dead, then it does not get a turn
		if (gobj->isDead()) {
			continue;
		}
		Turn turn = gobj->getTurn();
		GameObject* affectedgobj = 0; // the object that's affected by the turn
		bool doneTurn = this->doTurn(turn, gobj, flavor, affectedgobj); 

		// Elfs attack twice except on Drows
		if (gobj->subKind == ElfKind && turn.kind == Attack &&
			affectedgobj && affectedgobj->topKind == PlayerKind &&
			affectedgobj->subKind != DrowKind) {
			doneTurn = this->doTurn(turn, gobj, flavor, affectedgobj) && doneTurn;
		}

		// Tells the entity whether or not the turn succeeded
		gobj->turnSucceeded(turn, doneTurn, affectedgobj, flavor);
	}

	// Give all the information need to the display
	this->passInformationText();

	// Give all the flavor the display
	this->passFlavorText(flavor.str());
}

// Just calls the controller passInformation with the stuff it needs
void Game::passInformationText() const{
	this->controller->passInformationText(
			this->player->getAtkStat(),
			this->player->getDefStat(),
			this->player->getHP(),
			this->player->getMaxHP(),
			this->player->getGold(),
			this->player->getName(),
			this->levelNumber);
}

// Calls the controller passFlavor to give the display what it needs
void Game::passFlavorText(string text) const{
	this->controller->passFlavorText(text);
}


void Game::printNearByPotionsIfAny(LivingEntity* gobj, ostream& flavor) {
	if (gobj->topKind == PlayerKind) {
		int potionsNearBy = 0;
		string potions = "";

		// Checks a 1 lock radius
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				// We don't need to check the position we're on
				if (i == 0 && j == 0) {
					continue;
				}
				Vector p;
				p.x = i;
				p.y = j;
				GameObject* item = this->level->get(gobj->getPosition() + p);

				// We add a potion to display
				if (item && item->subKind == PotionKind) {
					Potion* potionObj = static_cast<Potion*>(item);
					potions += (potionsNearBy == 0 ? "" : ", ")
						// We check if the potion is known
						+ (gobj->isPotionKnown(potionObj->potionKind) ? item->getName()
															  : "Unknown Potion");
					potionsNearBy++;
				}
			}
		}

		// Give the flavor stream the potions
		if (potionsNearBy > 0) {
			flavor << "There " << (potionsNearBy == 1 ? " is " : " are ")
				   << potionsNearBy << (potionsNearBy == 1 ? " potion " : " potons ") << " around you: "
				   << potions << ". ";
		}
	}
}

bool Game::isPlayerDead() const {
	return this->getPlayer()->isDead();
}

bool Game::doTurn(Turn turn, LivingEntity* gobj,
				  ostream& flavor, GameObject*& affected) {
	Vector target = turn.target;
	Vector pos = gobj->getPosition();
	GameObject* tgobj = this->level->get(target + pos);
	affected = tgobj;

	bool turnSucceeded = false;

	// During different moves the Turn is different for every living entity
	switch (turn.kind) {
		case Move:
			{
				// We can only move to a free position
				if (!this->level->isFree(pos + target, gobj)) {
					break;
				}


				// Different types of movement options if the thing moving
				//   is the player
				if (gobj->topKind == PlayerKind) {
					// This is to pick up all the gold that's going to be under the player
					while (this->level->get(target + pos)
						&& this->level->get(target + pos)->subKind == GoldKind) {
						Gold* gold = static_cast<Gold*>(this->level->get(target + pos));
						// We can't pick up the dragon's gold yet..
						if (gold->goldKind == GoldDragonKind) {
							DragonGold* dgold = static_cast<DragonGold*>(gold);
							if (!dgold->dragon->isDead()) {
								break;
							}
						}

						// If we pick it up, we give it the player
						this->player->addGold(gold);
						flavor << "You picked up " << gold->getName()
							   << " (" << gold->value << "). ";

						// We make sure to the remove the gold from the level
						this->level->remove(gold->getPosition());
					}
				}

				// moves the potions from pos to the target position
				this->level->move(pos, pos + target);

				// We make sure to notify the controller with the changes
				//   to the state of the floor
				this->controller->notify(
						pos,
						this->level->getKindAt(pos));
				this->controller->notify(
						pos + target,
						gobj->subKind);
				
				turnSucceeded = true;
				break;
			}
		case Drink:
			// Drinking a potion is reserved for the player
			{
				bool drank = false;
				if (tgobj && tgobj->subKind == PotionKind) {
					gobj->drink(static_cast<Potion*>(tgobj));
					this->level->remove(target + pos);
					this->controller->notify(
							target + pos,
							this->level->getKindAt(target+pos));
					flavor << " You have drank a " 
						<< tgobj->getName() << ". ";
					drank = true;
				}

				if (!drank && gobj->topKind == PlayerKind) {
					flavor << " You can't drink weird things, man... ";
				}

				turnSucceeded = drank;
				break;
			}
		case Attack:
			{
				if (tgobj && 
				   (tgobj->topKind == EnemyKind ||
					tgobj->topKind == PlayerKind)) {

					LivingEntity* living =
						static_cast<LivingEntity*>(tgobj);

					// We nee to get the attack damage for the given living
					int damage = gobj->getAttackDamage(living);

					if (gobj->topKind == EnemyKind) {
						string attack_prompt = " attacks you ";
						if (gobj->subKind == DragonKind) {
							attack_prompt = " uses fire breath on you ";
						}
						flavor << gobj->getName()
							<< attack_prompt;
					}
					else {
						flavor << " You attack the "
							<< living->getName();
					}
					
					flavor << " for " << " " << damage << "    damage ";

					// We need to git the object with the attack
					bool hits = living->receiveAttack(
							gobj, damage);

					// Depending whether the attack hits or misses
					flavor << (hits ? " and it hits! " :
									  " and it misses! ")
						   << " ";

					// Print the remaining HP of the party being attacked
					flavor << living->getName() << " has " << living->getHP() << " HP left. ";

					// Handles the drops and removing the slain enemy
					if (living->isDead()) {
						this->level->remove(living->getPosition());
						living->drop();
						if (gobj->topKind == PlayerKind) {
							if (living->subKind != HumanKind &&
								living->subKind != MerchantKind &&
								living->subKind != DragonKind) {
								int goldToGive = living->slainGold();
								this->getPlayer()->addGold(goldToGive);
								flavor << " You just received " << goldToGive << " gold from " << living->getName() << ". ";
							}
						}

						// We need to notify the controller with the changes if something
						//   died
						this->controller->notify(
								living->getPosition(),
								this->level->getKindAt(living->getPosition()));
						flavor << " The " << living->getName() << " has been slain! ";
					}

					turnSucceeded = hits;;
					break;
				}

				if (gobj->topKind == PlayerKind) {
					flavor << " You tried to attack... nothing? ";
				}

				turnSucceeded = false;
				break;
			}
		default:
			turnSucceeded = false;
			break;
	}


	this->printNearByPotionsIfAny(gobj, flavor);

	return turnSucceeded;
}

void Game::clearNonPlayerObjects() {
	for (int i = 0; i < (int)this->statics->size(); i++) {
		delete this->statics->at(i);
	}

	for (int i = 0; i < (int)this->livings->size(); i++) {
		// Anything that is not a player we delete
		if (this->livings->at(i) != this->player) {
			delete this->livings->at(i);
		}
	}

	delete this->statics;
	delete this->livings;

	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();

	// We add the player back in if it already exists
	if (this->player) {
		this->livings->push_back(this->player);
	}

}

void Game::notifyWholeLevel() {
	Vector v;
	for (int i = 0; i < Global::levelHeight; i++) {
		v.y = i;
		for (int j = 0; j < Global::levelWidth; j++) {
			v.x = j;
			if (this->level->getKindAt(v) != NoneKind) {
				this->controller->notify(v,
					this->level->getKindAt(v));
			}
		}
	}
}

// Used to build a randomly generated level
void Game::buildRandomLevel() {
	this->preInitLevel();
	this->level->randomize();
	this->postInitLevel();
}

void Game::preInitLevel() {
	this->levelNumber++; // increase the level number
	this->clearNonPlayerObjects();
	delete this->level;
	this->level = 0;

	this->level = new Level(this);
	ifstream empty("./assets/layout1.txt"); // init the level to the empty level
	this->level->init(empty); // init the empty level
	empty.close();

}

void Game::postInitLevel() {
	this->level->place(
			this->player,
			this->level->getPlayerSpawn());

	this->player->resetEffect(); // we need to reset player effects

	// We need to pair gold to dragons, or add them if they don't have a pair
	for (int i = 0; i < (int)this->statics->size(); i++) {
		if (this->statics->at(i)->subKind == GoldKind) {
			Gold* gold = static_cast<Gold*>(this->statics->at(i));
			if (gold->goldKind == GoldDragonKind) {
				DragonGold* dgold = static_cast<DragonGold*>(this->statics->at(i));
				dgold->pair();
			}
		}
	}

	// We need to tell the View to remake the entire level
	this->notifyWholeLevel();
}

// Bulds a level given a set stream
void Game::buildLevel(istream& in) {
	this->preInitLevel();
	this->level->load(in);
	this->postInitLevel();
}

void Game::setController(Controller* controller) {
	this->controller = controller;
}

void Game::setPlayer(Kind kind) {
	GameObject* player = this->addObject(kind);
	this->player = static_cast<Player*>(player);
}

Player* Game::getPlayer() const {
	return this->player;
}

// Checks if we need to go to the next level
bool Game::goToNextLevel() const {
	GameObject* stairs = this->level->getStairs();

	Vector p = this->getPlayer()->getPosition();
	Vector s = stairs->getPosition();
	
	return p.x == s.x && p.y == s.y;
}

int Game::getLevelNumber() const {
	return this->levelNumber;
}

int Game::getCurrentScore() const {
	// Need a slightly different implementation for Shade
	if (this->getPlayer()->subKind == ShadeKind){
		return this->getPlayer()->getGold()*1.5;

	} else {

	return this->getPlayer()->getGold();
	}
}

Level* Game::getLevel() const {
	return this->level;
}

bool Game::merchantsHostile() const {
	return this->merchantsAttack;
}

void Game::makeMerchantsHostile() {
	this->merchantsAttack = true;
}


