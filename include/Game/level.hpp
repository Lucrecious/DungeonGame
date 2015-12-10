#ifndef LEVEL_H
#define LEVEL_H

#include <Utils/stack.hpp>
#include <Global/kind.hpp>
#include <Utils/vector.hpp>
#include <fstream>
#include <vector>
#include <Global/global.hpp>

class Game;
class GameObject;

class Level {
public:
	Level(Game*);
	~Level();

	void init(std::istream&);
	void load(std::istream&);
	void randomize();

	Vector getPlayerSpawn();
	
	void move(Vector, Vector);
	void place(GameObject*, Vector);

	bool isFree(Vector, GameObject*) const;

	GameObject* get(Vector) const;

	void remove(Vector);

	Kind getKindAt(Vector) const;

	GameObject* getStairs() const;

private:
	Game* game;
	GameObject* stairs;
	Stack<GameObject*>* tiles[Global::levelHeight][Global::levelWidth];

	void load(std::istream&, bool);

	Vector spawn;

	void charToObject(int, int, char, bool);

	Stack<GameObject*>* getStackAt(Vector) const;

	void addKindInRandomLocation(Kind);
	Vector getRandomFloorLocation(int chamber) const;
	int getRandomChamber() const;

	std::vector<Vector> chambers[Global::maxChambers];
};

#endif
