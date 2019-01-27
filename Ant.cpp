/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Ant.cpp
 */

#include <cstdlib>

#include "Ant.h"
#include "Sim.h"
#include "Grid.h"

#define ANTBREED 3

/**
 * Constructor for an Ant object
 * @return The Ant object
 */
Ant::Ant() {
	prey = true;
	grid = 0;
	lastBred = 0;
	xPosition = 0;
	yPosition = 0;
	moved = false;
}

/**
 * Constructor for an Ant object
 * @param x The x position for the Ant
 * @param y The y position for the Ant
 * @param grid The Grid of which the Ant is on
 */
Ant::Ant(int x, int y, Grid* gridPtr) {
	prey = true;
	grid = gridPtr;
	lastBred = 0;
	xPosition = x;
	yPosition = y;
	moved = false;
}

/**
 * Deconstructor for an Ant object
 * @return void
 */
Ant::~Ant() {
}

/**
 * Move function for an Ant object
 * @return void
 */
void Ant::move() {
	int* move = getRandomMoveToEmptyPoint(); // Holds possible move
	// Test if any possible move
	if(move != 0) {
		// If possible moves
		int newX = xPosition + move[0]; // Holds new X
		int newY = yPosition + move[1]; // Holds new Y
		grid->clearPoint(xPosition, yPosition);
		grid->setOrganismAt(newX, newY, this);
		xPosition = newX;
		yPosition = newY;
	}

	move = getRandomMoveToEmptyPoint();
	lastBred++;
	// Test if ant can breed
	if(lastBred > ANTBREED && move != 0) {
		// If ant can breed
		int newX = xPosition + move[0]; // holds new X
		int newY = yPosition + move[1]; // Holds new Y
		grid->setOrganismAt(newX, newY,
				new Ant(newX, newY, grid));
		lastBred = 0;
		incrementTotalAnts();
	}
	moved = true;
}
