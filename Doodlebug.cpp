/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Doodlebug.cpp
 */

#include "Doodlebug.h"
#include "Grid.h"
#include "Sim.h"

#define DOODLEBUGBREED 7
#define DOODLEBUGSTARVE 3

/**
 * Constructor for an Doodlebug object
 * @return The Doodlebug Object
 */
Doodlebug::Doodlebug() {
	prey = false;
	grid = 0;
	lastBred = 0;
	lastEaten = 0;
	xPosition = 0;
	yPosition = 0;
	moved = false;
}

/**
 * Constructor for an Doodlebug Object
 * @param x The x position for the Doodlebug
 * @param y The y position for the Doodlebug
 * @param grid The Grid of which the Doodlebug is on
 */
Doodlebug::Doodlebug(int x, int y, Grid* gridPtr) {
	prey = false;
	grid = gridPtr;
	lastBred = 0;
	lastEaten = 0;
	xPosition = x;
	yPosition = y;
	moved = false;
}

/**
 * Deconstructor for an Doodlebug Object
 * @return void
 */
Doodlebug::~Doodlebug() {
}

/**
 * Move function for an Doodlebug object
 * @return void
 */
void Doodlebug::move() {
	int* move = getRandomMoveToPrey();
	// Test if any prey to eat
	if(move != 0) {
		// If there are prey to eat
		int newX = xPosition + move[0]; // Holds new X
		int newY = yPosition + move[1]; // Holds new Y
		delete grid->getOrganismAt(newX, newY);
		grid->clearPoint(xPosition, yPosition);
		grid->setOrganismAt(newX, newY, this);
		xPosition = newX;
		yPosition = newY;
		lastEaten = 0;
	} else {
		// If no prey to eat
		move = getRandomMoveToEmptyPoint();
		// Test if any spaces to move
		if(move != 0) {
			// If spaces to move
			int newX = xPosition + move[0]; // Holds new X
			int newY = yPosition + move[1]; // Holds new Y
			grid->clearPoint(xPosition, yPosition);
			grid->setOrganismAt(newX, newY, this);
			xPosition = newX;
			yPosition = newY;
		}
	}

	lastEaten++;
	// Test if doodlebug is starved
	if(lastEaten > DOODLEBUGSTARVE) {
		// If doodlebug is starved
		grid->clearPoint(xPosition, yPosition);
		delete this;
		return;
	}

	move = getRandomMoveToEmptyPoint();
	lastBred++;
	// Test if doodlebug can breed
	if(lastBred > DOODLEBUGBREED && move != 0) {
		// If doodlebug can breed
		int newX = xPosition + move[0]; // Holds new X
		int newY = yPosition + move[1]; // Holds new Y
		grid->setOrganismAt(newX, newY,
				new Doodlebug(newX, newY, grid));
		lastBred = 0;
		incrementTotalDoodlebugs();
	}
	moved = true;
}
