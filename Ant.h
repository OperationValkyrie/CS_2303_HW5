/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Ant.h
 */

#ifndef ANT_H
#define ANT_H

#include "Organism.h"

class Grid;

class Ant: public Organism {
public:
	Ant();
	Ant(int x, int y, Grid *grid);
	~Ant();

	void move();
private:

};
#endif
