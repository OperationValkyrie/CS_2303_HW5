/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Organism.h
 */

#ifndef ORGANISM_H
#define ORGANISM_H

class Grid;

class Organism {
friend class Ant;
friend class Doodlebug;

public:
	Organism();
	Organism(bool preyType, int x, int y, Grid* gridPtr);
	virtual ~Organism();

	virtual void move();

	bool isPrey();

	int getLastBred();
	void incrementLastBred();
	void resetLastBred();

	int getXPosition();
	int getYPosition();

	bool getMoved();
	void setMoved(bool toggle);

	void print();

private:
	bool prey;
	Grid* grid;
	int lastBred;
	int xPosition;
	int yPosition;

	bool moved;

	int* getRandomMoveToEmptyPoint();
	int* getRandomMoveToPrey();
	int* getRandomMoveTo(int observe);
};
#endif
