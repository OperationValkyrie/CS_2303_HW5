/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 5
 * Grid.h
 */

#ifndef GRID_H
#define GRID_H

class Organism;

class Grid {
public:
	Grid();
	Grid(int oneDim, int doodlebugs, int ants);
	~Grid();

	Organism* getOrganismAt(int x, int y);
	void setOrganismAt(int x, int y, Organism* organism);
	void clearPoint(int x, int y);
	void clearAllPoints();

	bool isOccupied(int x, int y);
	bool isPrey(int x, int y);
	bool isPredator(int x, int y);

	bool hasOpenSpaces();
	bool hasPrey();
	bool hasPredators();

	int* getObservation(int x, int y);
	void runStep();

	int getNumberOfPrey();
	int getNumberOfPredators();

	void print();
private:
	int size; // Holds the dimension size of the square grid
	Organism*** theGrid; // Holds the grid

	void spawnDoodlebugs(int number);
	void spawnAnts(int number);

	int* getRandomOpenPoint();
};
#endif
