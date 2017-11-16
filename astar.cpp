#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "astar.hpp"

static void	clearNodeVector(std::vector<Node *> myVector) {
	std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Node *>::iterator it;
	while (myVector.size() > 0) {
		it = myVector.begin();
		delete(*it);
		myVector.erase(it);
	}

	std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

static Node		*swapNode(Node const &original, int const direction) {
	Node *newNode = new Node(original);
	newNode->depth += 1;
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

// static std::vector<Node *>::iterator  findNodeInVector(std::vector<Node *>  myVector, Node *target) {
// 	std::vector<Node *>::iterator it;
// 	size_t upBound = myVector.size();
// 	size_t downBound = 0;
// 	size_t vectorIndex = (upBound + downBound) / 2;
//
// 	// TODO: to optimize search do dicotomial search based on total score (depth + score)
//
// 	size_t targetScore = target->score + target->depth;
// 	size_t tmpScore;
// 	while (vectorIndex != downBound) {
// 		tmpScore = myVector[vectorIndex]->score + myVector[vectorIndex]->depth;
// 		if (tmpScore == targetScore) {
// 			// nodes where total score are equals are sorted by depth first
// 			// at first, adapt up/down bounds to the right depth
// 			// if
//
//
// 			// then iterate over all elem with same depth
// 		}
// 		else if (tmpScore > targetScore) { // look on the right side
// 			upBound = vectorIndex;
// 			vectorIndex = (upBound + downBound) / 2;
// 		}
// 		else if (tmpScore < targetScore) {  // look on the left side
// 			downBound = vectorIndex;
// 			vectorIndex = (upBound + downBound) / 2;
// 		}
// 	}
//
// 	return myVector.begin() + vectorIndex;
// }

// void printVector() {
//
// }

void		runAStar(Node *startNode) {
	// A* begin
	std::vector<Node *> openList;
	std::vector<Node *> closedList;
	std::vector<Node *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Point tmp;
	Node *tmpNode;
	int i; // counter for swaps in 4 directions
	std::vector<Node *>::iterator  vectorIndex;
	do {
		// TODO: choose node based on heuristic
		// std::cout << "\n --- Heuristic search ----------------------------------" << std::endl;
		it = openList.begin();
		tmpNode = *it;
		// Remove node from openList and put in closedList
		closedList.insert(closedList.begin(), *it);
		openList.erase(it);

		// std::cout << tmpNode->toString() << std::endl;
		// check if node is goal, if so exit loop
		if (tmpNode->score == 0) {
			break;
		}

		// foreach neighbour: check if already in one list + check if it's a shortest path
		tmp = tmpNode->points.find(0)->second;
		i = 0;
		Node *newNode;
		while (i < 4) {
			if ((i == 0 && tmp.y_current != 0) ||						// swap up
				(i == 1 && tmp.y_current != tmpNode->size - 1) ||			// swap down
				(i == 2 && tmp.x_current != 0) ||						// swap left
				(i == 3 && tmp.x_current != tmpNode->size - 1)) {			// swap right
				newNode = swapNode(*tmpNode, i);
				// std::cout << newNode->toString() << std::endl;
				// std::cout << "Searching.." << std::endl;
				vectorIndex = std::lower_bound(closedList.begin(), closedList.end(), newNode);
				// vectorIndex = vectorLowerBound(closedList, newNode);
				if (vectorIndex == closedList.end()) {
					vectorIndex = std::lower_bound(openList.begin(), openList.end(), newNode);
					if (vectorIndex == openList.end() || !(*vectorIndex == newNode)) {
						// std::cout << "Not found in open list, adding newNode to it" << std::endl;

						// std::cout << "Before:" << std::endl;
						// std::cout << tmpNode->toString() << std::endl;
						// printVector(openList);

						if (vectorIndex == openList.end())
							openList.push_back(newNode);
						else
							openList.insert(vectorIndex, newNode);


						// std::cout << "After:" << std::endl;
						// std::cout << tmpNode->toString() << std::endl;
						// printVector(openList);
					}
					// else
					// 	std::cout << "Already in open list" << std::endl;

				}
				// else
				// 	std::cout << "Found in closed list -> nothing to do" << std::endl;

				// check if node is in closedList
					// if not check if node is in openList
						// if in openList then check if depth is less, if so update prev node
						// if not in openList, then add it
				// std::cout << "" << std::endl;
			}
			// std::cout << "" << std::endl;
			i++;
		}

	} while (openList.size() > 0);

	// Reconstruct path to solution
	if (tmpNode->score != 0) {
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
