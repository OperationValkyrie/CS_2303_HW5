Jonathan Chang
CS 2303 C01 18
Assignment 5 - Polymorphism
README.txt

This program simulates a grid of prey and predators. Prey are able to move to empty points and after a certain number steps are able to breed a new prey into an adajcent point. Predators are able to move before any prey and will eat prey; if a predator does not eat after a certain number of steps it will starve and die. Predators will breed like prey - note that newly breed organisms cannot move until the next turn.

This program uses the follwing Objects:
Grid
Organism
Ant
Doodlebug
Where Ant and Doodlebug are subclasses of Organism. Also note the grid has a runStep() function which calls the virtual function move() on predators first and then prey. Each Organism is able to gain an observation of its surrounding through the getObservation() function of Grid. Using the getRandomMoveto() function, each Organism then uses that observation to generate an 2D array of possible moves of which it randomly chooses one.

To compile this program through the command line use the following command:
make all

To run this program through the command line use the following command:
./a.out size doodlebugs ants steps (seed) (pauseSteps)
Where:
size:       (int) size of one side of the square grid to simulate
doodlebugs: (int) the number of starting doodlebugs
ants:       (int) the number of startin ants
steps:      (int) the number of steps to simulate
seed:       (int) (optional) the seed to use for random movements
pauseSteps: (int) (optional) the number of steps to pause after (cycles) default = 0

This program can be complied in Eclipse by right-clicking on the project name and clicking Build Project.

This program can be run in Eclipse by using a Run Configuration with at least 4 arguements specificed above.

There were only two minor problems that occured during the writing of this program. Firstly, there was a case where a varaible was used before a it was intialized - this resulted in odd segementation faults until the faults was discovered. Secondly, since an organism is abl eto breed after it moves, there were out of bounds segementation faults during breeding. In order to fix this, a second observation happens after the first movement so that the correct observation is being used.

No external algorithms were used.

Example output can be found inside of Output1.txt and Output2.txt within the zip file.
