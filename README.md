# N-puzzle
42 project made with Nicolas Dudniczenko

### Objective
Create a program which solves N-puzzles (https://en.wikipedia.org/wiki/15_puzzle) using an implementation of the A* algorithm.

### Project's Constraints
The program must folllow the following constraints:
- Can choose between 3 different kinds of admissible heuristics (Manhattan distance is default)
- Can give a filepath for a starting configuration of the puzzle when launching the program
- If no filepath is given, the program must automatically generate a starting puzzle configuration
- The program must tell if the given puzzle is not solvable
- If the puzzle is solvable, at the end of execution the program must display the steps to solve the puzzle and also the total number of nodes in the open list and its max number of nodes

### Usage
$> ./n-puzzle [options] [input_file]

#### Options
  - -p _speed (min: 1, max: 5000)  ->  display slowly the solution.
  - -h  ->  display help menu and exits.
  - -e _heuristic  ->  use one heuristic: 'man' (for Manhattan distance), 'linear' (for Manhattan with linear conflict), 'misplaced' (for Misplaced tiles), 'all' (for Manhattan with linear conflict and misplaced tiles)
  - -s _size (min: 2, max: 100, default: 3)  ->  If you don't provide any input file, set a size for a random generated puzzle
  - -i _iterations (default: 10000)  ->  If you don't provide any input file, set a number of iterations for a random generated puzzle
  - -u  -> use uniform-cost search
  - -g  -> use greedy search

### Notes
- The 'all' heuristic is not an admissible one, but is the fastest one
- The '-g' option gives a not optimal solution, but it's faster than classic A* and it's way faster than '-u'
- A python script is given in order to generate a map and save it into a file
