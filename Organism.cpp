/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Organism.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Organism.h"
#include "Grid.h"

/*
 * Constructor for a generic organism
 * @return The Organism object
 */
Organism::Organism() {
	prey = false;
	lastBred = 0;
	grid = 0;
	xPosition = 0;
	yPosition = 0;
	moved = false;
}

/**
 * Constructor for an organism
 * @param preyType Whether this organism is prey or not
 * @param x The x position of this organism
 * @param y The y posiiton of this organism
 * @param gridPtr The grid that this organism is on
 * @return The Organism object
 */
Organism::Organism(bool preyType, int x, int y, Grid* gridPtr) {
	prey = preyType;
	xPosition = x;
	yPosition = y;
	grid = gridPtr;
	lastBred = 0;
	moved = false;
}

/**
 * Decontructor for an organism
 * @return void
 */
Organism::~Organism() {
}

/**
 * Move the current organism
 * @return void
 */
void Organism::move() {

}

/**
 * Gets whether the organism is prey or not
 * @return Whether the organism is prey or not
 */
bool Organism::isPrey() {
	return prey;
}

/**
 * Gets the number of turns since this organism last bred
 * @return The number of turns since this organism last bred
 */
int Organism::getLastBred() {
	return lastBred;
}

/**
 * Increments the number of turns since last bred
 * @return void
 */
void Organism::incrementLastBred() {
	lastBred++;
}

/**
 * Reset the number of turns since last bred to 0
 * @return void
 */
void Organism::resetLastBred() {
	lastBred = 0;
}

/**
 * Gets the current x position of the organism
 * @return The x position of the organism
 */
int Organism::getXPosition() {
	return xPosition;
}

/**
 * Gets the current y position of the organism
 * @return The y position of the organism
 */
int Organism::getYPosition() {
	return yPosition;
}

/**
 * Gets whether the organism has moved
 * @return Whether the organism has moved
 */
bool Organism::getMoved() {
	return moved;
}

/**
 * Sets whether the organism has moved
 * @param toggle What to set to
 * @return void
 */
void Organism::setMoved(bool toggle) {
	moved = toggle;
}

/**
 * Prints out this Organism
 * @return void
 */
void Organism::print() {
	cout << "P: " << prey << ", LB:" << lastBred << endl;
}

/**
 * Gets a possible move toward empty points
 * @return The possible move
 *
 * If no possible moves, returns 0
 */
int* Organism::getRandomMoveToEmptyPoint() {
	return getRandomMoveTo(0);
}

/**
 * Gets a possible move to prey
 * @return The possible move
 *
 * If no possible moves, returns 0
 */
int* Organism::getRandomMoveToPrey() {
	return getRandomMoveTo(1);
}

/**
 * Gets random move toward given observation
 * @param observe The observation to move to
 * @return The possible move
 *
 * If no possible moves, returns 0
 */
int* Organism::getRandomMoveTo(int observe) {
	int* observation = grid->getObservation(xPosition, yPosition);
	int numberMoves = 0; // Holds number of possible moves
	int allMoves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Holds all moves
	int** possibleMoves = new int*[4]; // Holds possible moves
	// Pre-conditions: No possible moves gotten
	for(int i = 0; i < 4; i++) {
		// Test if observation has object that looking for
		if(observation[i] == observe) {
			// If observation has the object
			possibleMoves[numberMoves] = allMoves[i];
			numberMoves++;
		}
	}
	// Post-conditions: All possible moves gotten
	// Test if any possible moves
	if(numberMoves !=0) {
		// If at least one move was found
		return possibleMoves[rand() % numberMoves];
	} else {
		// If no valid moves
		return 0;
	}
}
