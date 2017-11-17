#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "astar.hpp"

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

static Node		*swapNode(Node *original, int const direction) {
	Node *newNode = new Node(*original);
	newNode->depth += 1;
	newNode->prev = original;
	// TODO: set parent

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
	// std::cout << "Switching with: " << number << std::endl;

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

static std::vector<Node *>::iterator  dicoSearch(std::vector<Node *> &myVector, Node *targetNode) {
	size_t upBound = myVector.size();
	if (upBound == 0)
		return myVector.begin();
	else
		upBound--;
	size_t downBound = 0;
	size_t vectorIndex = (upBound + downBound) / 2;

	// TODO: to optimize search do dicotomial search based on total score (depth + score)

	// Fast checks if target is bigger/smaller than every element in vector
	if (*targetNode < *(myVector[downBound]))
		return myVector.begin();
	else if (*(myVector[downBound]) < *targetNode)
		return myVector.end();

	do {
		if (*targetNode < *(myVector[vectorIndex])) { // look on the right side
			upBound = vectorIndex;
			if (upBound > 0)
				upBound--;
			vectorIndex = (upBound + downBound) / 2;
		}
		else if (*(myVector[vectorIndex]) < *targetNode) {  // look on the left side
			// std::cout << "must search bigger" << std::endl;
			downBound = vectorIndex + 1;
			vectorIndex = (upBound + downBound) / 2;
		}
		else {
			// std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
			// iter from Down to Up to find exact match
			size_t tmpIndex = vectorIndex;
			while (vectorIndex >= downBound) {
				if (*(myVector[vectorIndex]) == *targetNode)
					return myVector.begin() + vectorIndex;
				if (vectorIndex == 0)
					return myVector.begin() + vectorIndex;
				vectorIndex--;
			}

			vectorIndex = tmpIndex;
			while (vectorIndex <= upBound) {
				if (*(myVector[vectorIndex]) == *targetNode)
					return myVector.begin() + vectorIndex;
				if (vectorIndex + 1 == 0)
					return myVector.begin() + vectorIndex;
				vectorIndex++;
			}
		}
	} while (vectorIndex != downBound);


	return myVector.begin() + vectorIndex;
}

static std::vector<Node *>::iterator  findNodeInVector(std::vector<Node *>  &myVector, Node *targetNode) {
	std::vector<Node *>::iterator it = myVector.begin();

	while (it != myVector.end()) {
		if (!(**it < *targetNode))
			break;
		it++;
	}

	return it;
}

void		runAStar(Node *startNode, bool fast) {
	// A* begin
	std::vector<Node *> openList;
	std::vector<Node *> closedList;
	std::vector<Node *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Point tmpPoint;
	Node *tmpNode;
	int i; // counter for swaps in 4 directions
	std::vector<Node *>::iterator  vectorIndex;
	Node *newNode;
	int x = 0;
	do {
		if (++x > 4)
			break;
		// TODO: choose node based on heuristic, take first if already sorted
		std::cout << "\n --- Heuristic search ----------------------------------" << std::endl;
		// std::cout << "Open" << std::endl;
		// printNodeVector(openList);
		// std::cout << "Closed" << std::endl;
		// printNodeVector(closedList);
		it = openList.begin();
		tmpNode = *it;

		// Remove node from openList and put in closedList
		if (fast)
			vectorIndex = dicoSearch(closedList, tmpNode);
		else
			vectorIndex = findNodeInVector(closedList, tmpNode);
		if (closedList.size() == 0 || vectorIndex == closedList.end())
			closedList.push_back(tmpNode);
		else {
			closedList.insert(vectorIndex, tmpNode);
		}
		openList.erase(it);

		// check if node is goal, if so exit loop
		if (tmpNode->score == 0) {
			break;
		}

		// foreach neighbour: check if already in one list + check if it's a shortest path
		tmpPoint = tmpNode->points.find(0)->second;
		i = 0;
		while (i < 4) {
			if ((i == 0 && tmpPoint.y_current != 0) ||						// swap up
				(i == 1 && tmpPoint.y_current != tmpNode->size - 1) ||			// swap down
				(i == 2 && tmpPoint.x_current != 0) ||						// swap left
				(i == 3 && tmpPoint.x_current != tmpNode->size - 1)) {			// swap right

				newNode = swapNode(tmpNode, i);
				std::cout << std::endl << "@" << std::endl << newNode->toString();

				if (fast)
					vectorIndex = dicoSearch(closedList, newNode);
				else
					vectorIndex = findNodeInVector(closedList, newNode);
				if (!(*vectorIndex == newNode)) {
					if (fast)
						vectorIndex = dicoSearch(openList, newNode);
					else
						vectorIndex = findNodeInVector(openList, newNode);
					if (openList.size() == 0 || vectorIndex == openList.end() || !(*vectorIndex == newNode)) {
						std::cout << "Offset: " << vectorIndex - openList.begin() << std::endl;
						if (openList.size() == 0 || vectorIndex == openList.end())
							openList.push_back(newNode);
						else {
							openList.insert(vectorIndex, newNode);
						}
					}

					// if in openList then check if depth is less, if so update prev node
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
