/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Sim.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#include "Sim.h"
#include "Grid.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

static int doodlebugTotal;
static int antTotal;

int main(int argc, char **argv) {

	int size; // Holds the size of the grid
	int doodlebugs; // Holds the number of Doodlebugs
	int ants; // Holds the number of Ants
	int steps; // Holds the number of steps
	int seed; // Holds the seed
	int pause; // Holds number of steps between pauses
	bool pauseIf; // Holds whether to pause or not

	// Test if incorrect number of arguments
	if(argc < 5 || argc > 7) {
		// If incorrect number of arguments
		cout << "Required Arguments:" << endl;
		cout << "  (int) one dimension of the square grid" << endl;
		cout << "  (int) number of doodlebugs to spawn" << endl;
		cout << "  (int) number of ants to spawn" << endl;
		cout << "  (int) number of steps to run through" << endl;
		cout << "Optional Arguemnts:" << endl;
		cout << "  (int) seed for organism spawning" << endl;
		cout << "  (int) number of steps between pauses" << endl;
		return EXIT_FAILURE;
	}

	// Set up arguments
	size = atoi(argv[1]);
	doodlebugs = atoi(argv[2]);
	ants = atoi(argv[3]);
	steps = atoi(argv[4]);

	doodlebugTotal = doodlebugs;
	antTotal = ants;

	seed = time(0);
	pause = 0;
	pauseIf = false;

	// Test if seed argument given
	if(argc > 6) {
		// If seed argument was given
		seed = atoi(argv[5]);
		// Test if given 0 seed
		if(seed == 0) {
			// If seed is 0
			seed = time(0);
		}
	}
	srand(seed); // Set the random seed

	// Test if pause argument was given
	if(argc == 7) {
		// If pause argument was given
		pause = atoi(argv[6]);
		// Test if given a integer larger than 0
		if(pause > 0) {
			// If given an integer larger than 0
			pauseIf = true;
		}
	}

	Grid* grid = new Grid(size, doodlebugs, ants);

	int step = 0; // Holds the current step
	int lastPause = 0; // Holds steps since last pause
	// Pre-conditions: No steps run
	while(step < steps && grid->hasPrey() && grid->hasPredators()) {
		// Loop Invariant: step < steps && grid has prey && grid has predators
		// Test if need to pause
		if(pauseIf && lastPause >= pause) {
			// If should pause
			cout << "Step:" << step << endl;
			grid->print();
			cout << endl;
			getchar();
			lastPause = 0;
		}
		grid->runStep();
		step++;
		lastPause++;
	}
	// Post-conditions: All valid steps ran
	// Print out log
	cout << "Command Line" << argv[0] << " " << argv[1] << " " << argv[2] << " "
			<< argv[3] << " " << argv[4];
	if(argc > 5) {
		cout << " " << argv[5];
	}
	if(argc > 6) {
		cout << " " << argv[6];
	}
	cout << endl;
	cout << "Number of Step Simulated: " << step << endl;
	cout << "Total DoodleBugs:         " << doodlebugTotal << endl;
	cout << "Ending DoodleBugs:        " << grid->getNumberOfPredators() << endl;
	cout << "Total Ants:               " << antTotal << endl;
	cout << "Ending Ants:              " << grid->getNumberOfPrey() << endl;
	cout << "Last Step:" << step << endl;
	grid->print();

	return 0;
}

/**
 * Increments the total number of ants
 * @return void
 */
void incrementTotalAnts() {
	antTotal++;
}

/**
 * Increments the total number of doodlebugs
 * @return void
 */
void incrementTotalDoodlebugs() {
	doodlebugTotal++;
}
