#include <View/textview.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <Global/global.hpp>
#include <map>
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

void TextView::setInformationText(Information i){
	this->informationText.str(string());
	this->informationText << "Atk: " << i.atkStat << setw(10);
	this->informationText << "Def: " << i.defStat << setw(10);
	this->informationText << "HP: " << i.currentHP << "/";

	if (i.name == "Vampire") {
		this->informationText << "-";
	}
	else {
		this->informationText << i.maxHP;
	}

	this->informationText << setw(10);
	this->informationText << "Gold: " << i.gold << setw(15);
	this->informationText << "Heals Left: " << i.healsLeft << setw(10);
	this->informationText << "Floor: " << i.level << endl;
	this->informationText << "Race: " << i.name;
}

void TextView::setFlavorText(string text) {
	this->flavorText.str(string());

	istringstream paragraph(text);

	string word;
	int lines = 0;
	int lineChars = 0;
	while (true) {
		paragraph >> word;
		if (paragraph.eof() || lines >= TextView::maxFlavorLines) {
			break;
		}
		
		if (lineChars + word.size() < Global::levelWidth * 3 / 4) {
			this->flavorText << word << " ";
			lineChars += word.size();
		}
		else {
			lines++;
			lineChars = 0;
			this->flavorText << endl << word << " ";
			lineChars += word.size();
		}
	}

	while (lines < TextView::maxFlavorLines) {
		lines++;
		this->flavorText << endl;
	}
}

void TextView::notify(Vector v, Kind k) {
	this->floor[v.y][v.x] = this->getCharFromKind(k);
}

char TextView::getCharFromKind(Kind kind) {
	if (TextView::kindChar.find(kind) == TextView::kindChar.end()) {
		return '?';
	}
	else {
		return TextView::kindChar[kind];
	}
}

map<Kind,char> TextView::kindChar = {
	{ FloorKind, Global::FloorSymbol },
	{ VWallKind, Global::VWallSymbol },
	{ HWallKind, Global::HWallSymbol },
	{ PassageKind, Global::PassageSymbol },
	{ DoorKind, Global::DoorSymbol },
	{ StairsKind, Global::StairsSymbol },
	{ PotionKind, Global::PotionSymbol },
	{ HumanKind, Global::HumanSymbol },
	{ DwarfKind, Global::DwarfSymbol },
	{ ElfKind, Global::ElfSymbol },
	{ OrcKind, Global::OrcSymbol },
	{ MerchantKind, Global::MerchantSymbol },
	{ HalflingKind, Global::HalflingSymbol },
	{ GoldKind, Global::GoldSymbol },
	{ DragonKind, Global::DragonSymbol },
	{ ShadeKind, Global::PlayerSymbol },
	{ GoblinKind, Global::PlayerSymbol },
	{ DrowKind, Global::PlayerSymbol },
	{ TrollKind, Global::PlayerSymbol },
	{ VampireKind, Global::PlayerSymbol }
};


