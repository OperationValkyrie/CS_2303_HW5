/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Doodlebug.h
 */

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Organism.h"

class Grid;

class Doodlebug: public Organism {
public:
	Doodlebug();
	Doodlebug(int x, int y, Grid *grid);
	~Doodlebug();

	void move();
private:
	int lastEaten;
};
#endif
