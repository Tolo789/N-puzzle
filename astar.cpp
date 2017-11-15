#include <vector>
#include <iostream>
#include <sstream>
#include <typeinfo> //
#include "astar.hpp"

static void	clearNodeVector(std::vector<Node *> myVector) {
	std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Node *>::iterator it = myVector.begin();
	while (myVector.size() > 0) {
		delete(*it);
		myVector.erase(it);
		it++;
	}

	std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

static Node		*swapNode(Node const &original, int const direction) {
	Node *newNode = new Node(original);

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

static std::vector<Node *>::iterator findNodeInVector(std::vector<Node *>  myVector, Node *target) {
	std::vector<Node *>::iterator it;

	// TODO: to optimize search do dicotomial search based on total score (depth + score)

	if (myVector.size() == 0)
		return myVector.end();
	it = myVector.begin();
	std::cout << "Type: " << typeid(myVector[myVector.size() / 2]).name() << std::endl;

	return it;
}

void		runAStar(Node *startNode) {
	// A* begin
	std::vector<Node *> openList;
	std::vector<Node *> closedList;
	std::vector<Node *>::iterator it;
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
		Node *newNode;
		while (i < 4) {
			if ((i == 0 && tmp.y_current != 0) ||						// swap up
				(i == 1 && tmp.y_current != (*it)->size - 1) ||			// swap down
				(i == 2 && tmp.x_current != 0) ||						// swap left
				(i == 3 && tmp.x_current != (*it)->size - 1)) {			// swap right
				newNode = swapNode(**it, i);
				std::cout << newNode->toString() << std::endl;
				findNodeInVector(openList, newNode);


				// check if node is in closedList
					// if not check if node is in openList
						// if in openList then check if depth is less, if so update prev node
						// if not in openList, then add it
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
	clearNodeVector(openList);
	clearNodeVector(closedList);
	return ;
}
