#include <Game/Game.hpp>
#include <Game/controller.hpp>
#include <vector>
#include <Game/Characters/shade.hpp>
#include <Game/Characters/human.hpp>
#include <Game/Characters/dwarf.hpp>
#include <Game/Characters/dragon.hpp>
#include <Game/Characters/elf.hpp>
#include <Game/Characters/orc.hpp>
#include <Game/Characters/merchant.hpp>
#include <Game/Characters/halfling.hpp>
#include <Game/Characters/goblin.hpp>
#include <Game/Characters/troll.hpp>
#include <Game/Characters/vampire.hpp>
#include <Game/Characters/drow.hpp>
#include <Game/Statics/dragongold.hpp>
#include <Game/Statics/potion.hpp>
#include <Game/Statics/gold.hpp>
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

GameObject* Game::addObject(Kind kind) {
	GameObject* gobj = 0;

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
	
	sort(this->livings->begin(),
		 this->livings->end(),
		 GameObject::less_than);

	ostringstream flavor("");

	for (int i = 0; i < (int)this->livings->size(); i++) {
		LivingEntity* gobj = this->livings->at(i);

		if (gobj->isDead()) {
			continue;
		}
		Turn turn = gobj->getTurn();
		GameObject* affectedgobj = 0; // the object that's affected by the turn
		bool doneTurn = this->doTurn(turn, gobj, flavor, affectedgobj); 

		if (gobj->subKind == ElfKind && turn.kind == Attack &&
			affectedgobj && affectedgobj->topKind == PlayerKind &&
			affectedgobj->subKind != DrowKind) {
			doneTurn = this->doTurn(turn, gobj, flavor, affectedgobj) && doneTurn;
		}

		gobj->turnSucceeded(turn, doneTurn, affectedgobj, flavor);
	}

	this->controller->passInformation();
	this->passFlavorText(flavor.str());
}

void Game::passFlavorText(string text) const{
	this->controller->passFlavorText(text);
}

void Game::printNearByPotionsIfAny(LivingEntity* gobj, ostream& flavor) const {
	if (gobj->topKind == PlayerKind) {
		int potionsNearBy = 0;
		string potions = "";

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) {
					continue;
				}
				Vector p;
				p.x = i;
				p.y = j;
				GameObject* item = this->level->get(gobj->getPosition() + p);

				if (item && item->subKind == PotionKind) {
					Potion* potionObj = static_cast<Potion*>(item);
					potions += (potionsNearBy == 0 ? "" : ", ")
						+ (gobj->isPotionKnown(potionObj->potionKind) ? item->getName()
															  : "Unknown Potion");
					potionsNearBy++;
				}
			}
		}

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

	switch (turn.kind) {
		case Move:
			{
				if (!this->level->isFree(pos + target, gobj)) {
					break;
				}

				if (gobj->topKind == PlayerKind) {
					while (this->level->get(target + pos)
						&& this->level->get(target + pos)->subKind == GoldKind) {
						Gold* gold = static_cast<Gold*>(this->level->get(target + pos));
						if (gold->goldKind == GoldDragonKind) {
							DragonGold* dgold = static_cast<DragonGold*>(gold);
							if (!dgold->dragon->isDead()) {
								break;
							}
						}

						this->player->addGold(gold);
						flavor << "You picked up " << gold->getName()
							   << " (" << gold->value << "). ";

						this->level->remove(gold->getPosition());
					}
				}

				this->level->move(pos, pos + target);

				this->controller->notify(pos, this->level->getKindAt(pos));
				this->controller->notify(pos + target, gobj->subKind);
				
				turnSucceeded = true;
				break;
			}
		case Drink:
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

					int damage = gobj->getAttackDamage(living);

					if (gobj->topKind == EnemyKind) {
						string attack_prompt = " attacks you ";
						if (gobj->subKind == DragonKind) {
							attack_prompt = " uses fire breath on you ";
						}
						flavor << gobj->getName() << attack_prompt;
					}
					else {
						flavor << " You attack the " << living->getName();
					}
					
					flavor << " for " << damage << " damage ";

					bool hits = living->receiveAttack(
							gobj, damage);

					flavor << (hits ? " and it hits!" : " and it misses!") << " ";
					flavor << living->getName() << " has " << living->getHP() << " HP left. ";

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
		case Heal:
			{
				string healText;
				if (gobj->getHealsLeft() > 0) {
					gobj->useHeal();
					healText = " You used a heal. ";
				}
				else {
					healText = " You don't have any heals left. ";
				}

				if (gobj->topKind == PlayerKind) {
					flavor << healText;
				}
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
		if (this->livings->at(i) != this->player) {
			delete this->livings->at(i);
		}
	}

	delete this->statics;
	delete this->livings;

	this->statics = new vector<StaticEntity*>();
	this->livings = new vector<LivingEntity*>();

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

void Game::buildRandomLevel() {
	this->preInitLevel();
	this->level->randomize();
	this->postInitLevel();
}

void Game::preInitLevel() {
	this->levelNumber++;
	this->clearNonPlayerObjects();
	delete this->level;
	this->level = 0;

	this->level = new Level(this);
	ifstream empty("./assets/layout1.txt");
	this->level->init(empty);
	empty.close();

}

void Game::postInitLevel() {
	this->level->place(
			this->player,
			this->level->getPlayerSpawn());

	for (int i = 0; i < (int)this->statics->size(); i++) {
		if (this->statics->at(i)->subKind == GoldKind) {
			Gold* gold = static_cast<Gold*>(this->statics->at(i));
			if (gold->goldKind == GoldDragonKind) {
				DragonGold* dgold = static_cast<DragonGold*>(this->statics->at(i));
				dgold->pair();
			}
		}
	}

	this->notifyWholeLevel();
}

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
