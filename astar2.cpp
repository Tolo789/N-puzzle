#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "astar2.hpp"

static void	clearNodeVector(std::vector<Node *> &myVector) {
	std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Node *>::iterator it;
	while (myVector.size() > 0) {
		it = myVector.begin();
		delete(*it);
		myVector.erase(it);
	}

	std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

static void printNodeVector(std::vector<Node *> &myVector) {
	std::vector<Node *>::iterator it = myVector.begin();
	while (it != myVector.end()) {
		std::cout << (*it)->toString() << std::endl;
		it++;
	}
}

static bool isNodeInVector(std::vector<Node *> &myVector, Node *targetNode) {
	std::vector<Node *>::iterator it = myVector.begin();
	while (it != myVector.end()) {
		if (**it == *targetNode)
			return true;
		it++;
	}

	return false;
}


static std::vector<Node *>::iterator getBestNode(std::vector<Node *> &myVector) {
	std::vector<Node *>::iterator best = myVector.begin();
	std::vector<Node *>::iterator it = myVector.begin();

	while (it != myVector.end()) {
		if (**it < **best)
			best = it;
		it++;
	}

	return best;
}

static Node		*swapNode(Node *original, int const direction) {
	Node *newNode = new Node(*original);
	newNode->depth += 1;
	newNode->prev = original;

	Point &zero = newNode->points[0];
	size_t number = 0;
	switch (direction) {
		case 0: // up
			number = newNode->array[zero.y_current - 1][zero.x_current];
			break;
		case 1: // down
			number = newNode->array[zero.y_current + 1][zero.x_current];
			break;
		case 2: // left
			number = newNode->array[zero.y_current][zero.x_current - 1];
			break;
		case 3: // right
			number = newNode->array[zero.y_current][zero.x_current + 1];
			break;
		default:
			break;
	}

	Point &other = newNode->points[number];

	// Update array
	newNode->array[other.y_current][other.x_current] = 0;
	newNode->array[zero.y_current][zero.x_current] = number;

	// Update points coord
	number = zero.x_current;
	zero.x_current = other.x_current;
	other.x_current = number;
	number = zero.y_current;
	zero.y_current = other.y_current;
	other.y_current = number;

	newNode->updateScore();

	return (newNode);
}

void		runAStar2(Node *startNode, bool fast) {
	// A* begin
	std::vector<Node *> openList;
	std::vector<Node *> closedList;
	std::vector<Node *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Node *tmpNode;
	int i; // counter for swaps in 4 directions
	Node *newNode;
	do {
		// TODO: choose node based on heuristic, take first if already sorted
		// std::cout << "\n --- Heuristic search ----------------------------------" << std::endl;
		// std::cout << "Open" << std::endl;
		// printNodeVector(openList);
		// std::cout << "Closed" << std::endl;
		// printNodeVector(closedList);

		it = getBestNode(openList);
		tmpNode = *it;

		// Remove node from openList and put in closedList
		closedList.push_back(tmpNode);
		openList.erase(it);

		// check if node is goal, if so exit loop
		if (tmpNode->score == 0) {
			break;
		}

		// foreach neighbour: check if already in one list + check if it's a shortest path
		i = 0;
		while (i < 4) {
			if ((i == 0 && tmpNode->points[0].y_current != 0) ||						// up
				(i == 1 && tmpNode->points[0].y_current != tmpNode->size - 1) ||		// down
				(i == 2 && tmpNode->points[0].x_current != 0) ||						// left
				(i == 3 && tmpNode->points[0].x_current != tmpNode->size - 1)) {		// right

				newNode = swapNode(tmpNode, i);
				if (!isNodeInVector(closedList, newNode)) {
					if (!isNodeInVector(openList, newNode)) {
						openList.push_back(newNode);
					}
					// else {
					// 	// TODO: if in openList then check if depth is less, if so update prev node
					// }
				} else {
					delete newNode;
				}
			}
			i++;
		}

	} while (openList.size() > 0);
	std::cout << " ------------------------------------------------------------" << std::endl;

	// Reconstruct path to solution
	if (tmpNode->score != 0) {
		std::cout << "Solution not found" << std::endl;
	}
	else {
		std::cout << "Solution found!" << std::endl;
		do {
			std::cout << tmpNode->toString() << std::endl;
			tmpNode = tmpNode->prev;
		} while (tmpNode);
	}

	// Clear vectors
	clearNodeVector(openList);
	clearNodeVector(closedList);
	return ;
}
