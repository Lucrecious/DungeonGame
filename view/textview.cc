#include "textview.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../globals/global.h"
using namespace std;

TextView::TextView(int w, int h) : width(w), height(h) {
	this->floor = new char*[h];
	for (int i = 0; i < h; i++) {
		this->floor[i] = new char[w];
		for (int j = 0; j < w; j++) {
			this->floor[i][j] = ' ';
		}
	}
}

TextView::~TextView() {
	for (int i = 0; i < this->height; i++) {
		delete[] this->floor[i];
	}
	delete[] this->floor;
}

void TextView::display() const {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			cout << this->floor[i][j];
		}
		cout << endl;
	}
	cout << this->informationText.str() << endl;
	cout << this->flavorText.str() << endl;
}

void TextView::setInformationText(
		int atk, int def, int hp, int hpmax, int gold, string race, int level) {
	this->informationText.str(string());
	this->informationText << "Atk: " << atk << setw(10);
	this->informationText << "Def: " << def << setw(10);
	this->informationText << "HP: " << hp << "/" << (race == "Vampire" ? 0 : hpmax)
						  << setw(10);
	this->informationText << "Gold: " << gold << setw(30);
	this->informationText << "Floor: " << level << endl;
	this->informationText << "Race: " << race;
}

void TextView::setFlavorText(string text) {
	this->flavorText.str(string());
	this->flavorText << text;
}

void TextView::notify(Vector v, Kind k) {
	this->floor[v.y][v.x] = this->getCharFromKind(k);
}

char TextView::getCharFromKind(Kind kind) {
	switch(kind) {
		case FloorKind:
			return Global::FloorSymbol;
		case VWallKind:
			return Global::VWallSymbol;
		case HWallKind:
			return Global::HWallSymbol;
		case PassageKind:
			return Global::PassageSymbol;
		case DoorKind:
			return Global::DoorSymbol;
		case StairsKind:
			return Global::StairsSymbol;
		
		case PotionKind:
			return Global::PotionSymbol;

		case HumanKind:
			return Global::HumanSymbol;
		case DwarfKind:
			return Global::DwarfSymbol;
		case ElfKind:
			return Global::ElfSymbol;
		case OrcKind:
			return Global::OrcSymbol;
		case MerchantKind:
			return Global::MerchantSymbol;
		case HalflingKind:
			return Global::HalflingSymbol;

		case GoldKind:
			return Global::GoldSymbol;

		case DragonKind:
			return Global::DragonSymbol;

		case ShadeKind:
		case GoblinKind:
		case DrowKind:
		case TrollKind:
		case VampireKind:
		case PlayerKind:
			return Global::PlayerSymbol;
		default:
			return '?';
	}
}




