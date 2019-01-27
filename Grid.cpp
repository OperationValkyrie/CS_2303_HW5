/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Grid.h
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Grid.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

/**
 * Constructor for a Grid object
 * @return The Grid object
 */
Grid::Grid() {
	theGrid = 0;
	size = 0;
}

/**
 * Constructor for a Grid object
 * @param oneDim The dimension size of one side of square
 * @param doodlebugs The number of doodlebugs to spawn
 * @param ants The number of ants to spawn
 * @return The Grid object
 */
Grid::Grid(int oneDim, int doodlebugs, int ants) {
	size = oneDim;
	theGrid = new Organism**[size];
	// Pre-conditions: theGrid not yet set
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		theGrid[i] = new Organism*[size];
		// Pre-conditions: The grid row not yet set
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			theGrid[i][j] = 0;
		}
		// Post-conditions: The grid row is set
	}
	// Post-conditions: theGrid is set to empty
	clearAllPoints();
	spawnDoodlebugs(doodlebugs);
	spawnAnts(ants);
}

/**
 * Decontructor for a Grid object
 * @return void
 *
 * Also deconstructs all Organism in the Grid
 */
Grid::~Grid() {
	// Pre-conditions: Grid object not yet deleted
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: Grid row not yet deleted
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			delete theGrid[i][j];
		}
		// Post-conditions: Grid row deleted
	}
	// Post-conditions: Grid object deleted
}

/*
 * Gets the Organism at a particular point
 * @return The Organism at the point
 *
 * If not Organism, returns null pointer
 */
Organism* Grid::getOrganismAt(int x, int y) {
	return theGrid[x][y];
}

/**
 * Sets the Organism at a particular point
 * @param x The x position
 * @param y The y position
 * @param organism The organism to set
 */
void Grid::setOrganismAt(int x, int y, Organism* organism) {
	theGrid[x][y] = organism;
}

/**
 * Clears out the given point
 * @param x The x position
 * @param y The y position
 */
void Grid::clearPoint(int x, int y) {
	theGrid[x][y] = 0;
}

/**
 * Clears all points in the grid
 * @return void
 */
void Grid::clearAllPoints() {
	// Pre-conditions: No points cleared yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No points in row cleared yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			theGrid[i][j] = 0;
		}
		// Post-conditions: All points in row cleared
	}
	// Post-conditions: All points cleared
}

/**
 * Tests if the given point is occupied
 * @return Whether the given point is occupied
 */
bool Grid::isOccupied(int x, int y) {
	return theGrid[x][y] != 0;
}

/**
 * Tests if the given point is occupied and is a prey
 * @param x The x position of the point
 * @param y The y posiiton of the point
 */
bool Grid::isPrey(int x, int y) {
	return isOccupied(x, y) && getOrganismAt(x,y)->isPrey();
}

/**
 * Tests if the given point is occupied and is a predator
 * @param x The x position of the point
 * @param y The y posiiton of the point
 */
bool Grid::isPredator(int x, int y) {
	return isOccupied(x , y) && !getOrganismAt(x,y)->isPrey();
}

/**
 * Tests if any open spaces still on the grid
 * @return Whether there are any open spaces
 */
bool Grid::hasOpenSpaces() {
	// Pre-conditions: No points checked yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No points in row checked yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if the point is empty
			if(theGrid[i][j] == 0) {
				// If the point is empty
				return true;
			}
		}
		// Post-conditions: All points in row checked
	}
	// Pre-conditions: All points checked
	return false;
}

/**
 * Tests if there are any prey still on the grid
 * @return Whether there are any prey on the grid
 */
bool Grid::hasPrey() {
	// Pre-conditions: No points checked yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No points in row checked yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if the point is occupied as is prey
			if(isOccupied(i, j) && getOrganismAt(i, j)->isPrey()) {
				// If the point contains a prey
				return true;
			}
		}
		// Post-conditions: All points in row checked
	}
	//Post-conditions: All points checked
	return false;

}

/**
 * Tests if there are any predators still on the grid
 * @return Whether there are any predators on the grid
 */
bool Grid::hasPredators() {
	// Pre-conditions: No points checked yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No points in row checked yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if points is occupied and is predator
			if(isOccupied(i, j) && !getOrganismAt(i, j)->isPrey()) {
				// If the points contains a predator
				return true;
			}
		}
		// Post-conditions: All points in row checked
	}
	// Post-conditions: All points checked
	return false;

}

/**
 * Gets the observational data from a certain point
 * @param x The x position to get data for
 * @param y The y position to get data for
 * @return The observational data
 *
 * Observation data is returned as a int array of size 4
 * 		0 -> Top
 * 		1 -> Bottom
 * 		2 -> Left
 * 		3 -> Right
 * Data is returned as
 * 		0 -> Empty Space
 * 		1 -> Prey
 * 		2 -> Predator
 * 		3 -> Wall
 */
int* Grid::getObservation(int x, int y) {
	int* observation = new int[4];
	// Test if point is in first row
	if(x != 0) {
		// If not in first row
		// Test if point contains prey
		if(isPrey(x - 1, y)) {
			// If point contains prey
			observation[0] = 1;
		// Test if point contains predator
		} else if(isPredator(x - 1, y)) {
			// If point contains predator
			observation[0] = 2;
		} else {
			// If point contains neither prey nor predator
			observation[0] = 0;
		}
	} else {
		// If point is in first row
		observation[0] = 3;
	}
	// Test if point is in last row
	if(x != size - 1) {
		// If not in last row
		// Test if point contains prey
		if(isPrey(x + 1, y)) {
			// If point contains prey
			observation[1] = 1;
		// Test if point contains predator
		} else if(isPredator(x + 1, y)) {
			// If point contains predator
			observation[1] = 2;
		} else {
			// If point contains neither prey nor predator
			observation[1] = 0;
		}
	} else {
		// If point is inlast row
		observation[1] = 3;
	}
	// Test if point is in first column
	if(y != 0) {
		// If point is not in first column
		// Test if point contains prey
		if(isPrey(x, y - 1)) {
			// If point contains prey
			observation[2] = 1;
		// Test if point contains predator
		} else if(isPredator(x, y - 1)) {
			// If point contains predator
			observation[2] = 2;
		} else {
			// If point contains neither prey not predator
			observation[2] = 0;
		}
	} else {
		// If point is in first column
		observation[2] = 3;
	}
	// Test if point is not in last column
	if(y != size - 1) {
		// If point is not in last column
		// Test if point contains prey
		if(isPrey(x, y + 1)) {
			// If point contains prey
			observation[3] = 1;
		// Tests if pint contains predator
		} else if(isPredator(x, y + 1)) {
			// If point contains predator
			observation[3] = 2;
		} else {
			// If point contains neither prey nor predator
			observation[3] = 0;
		}
	} else {
		// If point is in last column
		observation[3] = 3;
	}
return observation;
}

/**
 * Runs through a single step on the grid
 * @return void
 */
void Grid::runStep() {
	// Pre-condtiions: No predators moved yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No predators in row moved yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if point contains a predator
			if(isOccupied(i, j) && !isPrey(i, j) &&
					!getOrganismAt(i,j)->getMoved()) {
				// If the point contains a predator
				getOrganismAt(i, j)->move();
			}
		}
		// Post-conditions: All predators in row moved
	}
	// Post-conditions: All predators moved
	// Pre-conditions: No prey moved yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No prey in row moved yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if point contains prey
			if(isOccupied(i, j) && isPrey(i, j) &&
					!getOrganismAt(i, j)->getMoved()) {
				// If point contains prey
				getOrganismAt(i, j)->move();
			}
		}
		// Post-conditions: All prey in row moved
	}
	// Post-conditions: All prey moved
	// Pre-conditions: No organisms reset
		for(int i = 0; i < size; i++) {
			// Loop Invariant: 0 < i < size
			// Pre-conditions: No organism in row reset yet
			for(int j = 0; j < size; j++) {
				// Loop Invariant: 0 < j < size
				// Test if point contains organism
				if(isOccupied(i, j)) {
					// If point contains organism
					getOrganismAt(i, j)->setMoved(false);
				}
			}
			// Post-conditions: All organisms in row reset
		}
		// Post-conditions: All organisms reset
}

/**
 * Gets the total number of prey on the grid
 * @return The total number of prey on the grid
 */
int Grid::getNumberOfPrey() {
	int total = 0; // Holds total number
	// Pre-conditions: No prey counted yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No prey in row counted yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if point is prey
			if(isOccupied(i, j) && isPrey(i, j)) {
				// If point is prey
				total++;
			}
		}
		// Post-conditions: All prey in row counted
	}
	// Pre-conditions: All prey counted
	return total;
}

/**
 * Gets the total number of predators on the grid
 * @return The total number of predators on the grid
 */
int Grid::getNumberOfPredators() {
	int total = 0; // Holds total number
	// Pre-conditions: No predators counted yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		// Pre-conditions: No predators in row counted yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if point is predator
			if(isOccupied(i, j) && !isPrey(i, j)) {
				// If point is predator
				total++;
			}
		}
		// Post-conditions: All predators in row counted
	}
	// Pre-conditions: All predators counted
	return total;
}

/**
 * Prints out the grid
 * @return void
 *
 * Prey is represents by 'o's
 * Predators are represented by 'x'
 */
void Grid::print() {
	// Pre-conditions: No points printed yet
	for(int i = 0; i < size; i++) {
		// Loop Invariant: 0 < i < size
		//Pre-conditions: No points in row printed yet
		for(int j = 0; j < size; j++) {
			// Loop Invariant: 0 < j < size
			// Test if point is empty
			if(theGrid[i][j] == 0) {
				// If point was empty
				cout << '-';
			// Test if point contains prey
			} else if(theGrid[i][j]->isPrey()){
				// If point contains prey
				cout << 'o';
			} else {
				// If point contains neither nothing nor prey
				cout << 'x';
			}
		}
		// Post-conditions: All points in row printed
		cout << endl;
	}
	// Post-conditions: All points printed
}

/**
 * Spawns the given number of Doodlebugs on the grid
 * @param number The number of Doodlebugs to spawn
 * @return void
 *
 * There must be enough open spaces for the number of Doodlebugs
 * 		if not, will only added until grid is filled
 */
void Grid::spawnDoodlebugs(int number) {
	// Pre-conditions: No Doodlebugs spawned yet
	for(int i = 0; i < number; i++) {
		// Loop Invariant: 0 < i < number
		// Test if grid is filled
		if(!hasOpenSpaces()) {
			// If grid is filled
			return;
		}
		int* point = getRandomOpenPoint();
		int x = point[0];
		int y = point[1];
		theGrid[x][y] = new Doodlebug(x, y, this);
	}
	// Post-conditions: All DoodleBugs spawned
}

/**
 * Spawns the given number of Ants on the grid
 * @param number The number of Ants to spawn
 * @return void
 *
 * There must be enough open spaces for the number of Ants
 * 		if not, will only added until grid is filled
 */
void Grid::spawnAnts(int number) {
	// Pre-conditions: No Ants spawned yet
	for(int i = 0; i < number; i++) {
		// Loop Invariant: 0 < i < number
		// Test if grid is filled
		if(!hasOpenSpaces()) {
			// If grid is filled
			return;
		}
		int* point = getRandomOpenPoint();
		int x = point[0];
		int y = point[1];
		theGrid[x][y] = new Ant(x, y, this);
	}
	// Post-conditions: All Ants spawned
}

/**
 * Gets a random open point
 * @return An int array with index 0 -> x and 1 -> y
 *
 * Must has at least one empty point on grid
 * 		If not returns [-1,-1];
 */
int * Grid::getRandomOpenPoint() {
	int* point = new int[2];
	// Test if grid is filled
	if(!hasOpenSpaces()) {
		// If grid is filled
		point[0] = -1;
		point[1] = -1;
		return point;
	}
	int x = rand() % size;
	int y = rand() % size;
	// Pre-conditions: Valid x and y not yet found
	while(isOccupied(x, y)) {
		/*
		x = rand() % size;
		y = rand() % size;
		*/

		y++;
		// Test if over last column
		if(x != size - 1 && y == size) {
			// If over last column
			x++;
			y = 0;
		// Test if over last row and last column
		} else if (x == size - 1 && y == size) {
			// If over last row and column
			x = 0;
			y = 0;
		}

	}
	// Post-conditions: Valid x and y or grid is filled
	point[0] = x;
	point[1] = y;
	return point;
}
