#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Map.class.hpp"

std::string		**treatInput(std::string input) {
	std::vector<std::string>	splitLine;
	std::string		**ret;
	std::string					line;
	std::istringstream			f(input);

	while (getline(f, line, '\n')) {
		splitLine.push_back(line);
	}
	std::cout << splitLine.size() << std::endl;
	size_t	splitLineSize = splitLine.size();
	ret = new std::string* [splitLineSize];
	for (size_t i = 0; i < splitLineSize; i++) {
		std::istringstream	p(splitLine[i]);
		std::vector<std::string>	subSplitLine;
		while (getline(p, line, ' ')) {
			subSplitLine.push_back(line);
		}
		ret[i] = new std::string [subSplitLine.size()];
		for (size_t j = 0; j < subSplitLine.size(); j++) {
			ret[i][j] = std::string(subSplitLine[j]);
		}
	}
	return (ret);
}

void	clearMapVector(std::vector<Map *> myVector) {
	std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Map *>::iterator it = myVector.begin();
	while (myVector.size() > 0) {
		delete(*it);
		myVector.erase(it);
		it++;
	}

	std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

Map		*swapNode(Map &original, int direction) {
	Map *newNode = new Map(original);

	std::map<size_t, Point>::iterator zero = newNode->points.find(0);
	std::map<size_t, Point>::iterator other;
	size_t number = 0;
	switch (direction) {
		case 0: // up
			number = newNode->array[zero->second.y_current - 1][zero->second.x_current];
			break;
		case 1: // down
			number = newNode->array[zero->second.y_current + 1][zero->second.x_current];
			break;
		case 2: // left
			number = newNode->array[zero->second.y_current][zero->second.x_current - 1];
			break;
		case 3: // right
			number = newNode->array[zero->second.y_current][zero->second.x_current + 1];
			break;
		default:
			break;
	}
	other = newNode->points.find(number);
	std::cout << "Switching with: " << number << std::endl;

	// Update array
	newNode->array[other->second.y_current][other->second.x_current] = 0;
	newNode->array[zero->second.y_current][zero->second.x_current] = number;

	// Update points coord
	number = zero->second.x_current;
	zero->second.x_current = other->second.x_current;
	other->second.x_current = number;
	number = zero->second.y_current;
	zero->second.y_current = other->second.y_current;
	other->second.y_current = number;

	newNode->updateScore();

	return (newNode);
}

int		main(int ac, char **av) {
	std::string **ret = treatInput("1 2 3\n8 5 4\n7 0 6");
	Map *startNode = new Map(3, ret);

	// find specific point in map
	// Point tmp = startNode->points.find(4)->second;
	// std::cout << std::endl << "Test for find in map:" << std::endl;
	// std::cout << tmp.toString();
	// // test if map is well linked with array
	// std::cout << startNode->array[tmp.y_current][tmp.x_current] << std::endl;


	// A* begin
	std::vector<Map *> openList;
	std::vector<Map *> closedList;
	std::vector<Map *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Point tmp;
	int i; // counter for swaps in 4 directions
	do {
		// TODO: choose node based on heuristic
		it = openList.begin();

		std::cout << (*it)->toString() << std::endl;
		// check if node is goal, if so exit loop
		if ((*it)->score == 0) {
			break;
		}

		// foreach neighbour: check if already in one list + check if it's a shortest path
		tmp = (*it)->points.find(0)->second;
		i = 0;
		Map *newNode;
		while (i < 4) {
			if ((i == 0 && tmp.y_current != 0) ||						// swap up
				(i == 1 && tmp.y_current != (*it)->size - 1) ||			// swap down
				(i == 2 && tmp.x_current != 0) ||						// swap left
				(i == 3 && tmp.x_current != (*it)->size - 1)) {			// swap right
				newNode = swapNode(**it, i);
				std::cout << newNode->toString() << std::endl;
			}
			i++;
		}



		// Remove node from openList and put in closedList
		closedList.insert(closedList.begin(), *it);
		openList.erase(it);
		it = openList.end();

	} while (openList.size() > 0);

	// Reconstruct path to solution
	if (it == openList.end()) {
		std::cout << "Solution not found" << std::endl;
	}
	else {
		std::cout << "Solution found" << std::endl;
	}

	// Clear vectors
	clearMapVector(openList);
	clearMapVector(closedList);



	delete [] ret[0];
	delete [] ret[1];
	delete [] ret[2];
	delete [] ret;
	return 0;
}
