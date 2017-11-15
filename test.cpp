#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Node.class.hpp"
#include "Env.class.hpp"
#include "options_handling.hpp"
#include "error.hpp"

#include <stdio.h>//

static std::string		**treatInput(std::string input) {
	std::vector<std::string>	splitLine;
	std::string					**ret;
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
void	clearNodeVector(std::vector<Node *> myVector) {
	std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Node *>::iterator it = myVector.begin();
	while (myVector.size() > 0) {
		delete(*it);
		myVector.erase(it);
		it++;
	}

	std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

Node		*swapNode(Node const &original, int const direction) {
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

static int	read_file(char const *filename, std::string *input) {
	std::fstream		file;
	std::string			line;
	std::stringstream	sstream;

	if ( !filename ) {
		return ( 0 );
	} else {
		std::cout << filename << '\n';
		file.open( filename, std::ios::in );
		if ( file.is_open() ) {
			while ( getline(file, line) ) {
				sstream << line << '\n';
			}
			*input = sstream.str();
			return ( 0 );
		} else {
			return ( ft_error(INVALID_FILENAME, -1) );
		}
		return ( 0 );
	}
}

static int		usage(char const *bin) {
	std::cout << "Usage: " << bin << " [options] [input_file]" << std::endl << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  -" << HELP_CHAR << ": display help menu and exits." << std::endl;
	std::cout << "  -" << HEUR_CHAR << " <heuristic>: (default: man)" << std::endl;
	std::cout << "    heuristics:" << std::endl;
	std::cout << "      '" << HEUR_MAN_STR << "' : Manhattan" << std::endl;
	std::cout << "      '" << HEUR_2_STR << "' : ..." << std::endl;
	std::cout << "      '" << HEUR_3_STR << "' : ..." << std::endl;
	std::cout << "  /* If you don't provide any input file */" << std::endl;
	std::cout << "  -" << SIZE_CHAR << " <size> (default: 3): set a size for a random generated puzzle" << std::endl;
	std::cout << "  -" << ITERATIONS_CHAR << " <iterations> (default: 10000): set a number of iterations for a random generated puzzle" << std::endl;
	return (1);
}

int		run(Node *startNode) {
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



	return 0;
}

int				main(int ac, char **av) {
	Env				*env;
	std::string		*input;

	t_puzzle p = {0, 0};
	env = new Env();
	input = NULL;
	// if (ac == 1) {
		// return (usage(av[0]));
	if ( get_options(env, &ac, av) ) {
		return (1);
	} else if ( env->options & HELP ) {
		return (usage(av[0]));
	} else if ( ac > 2 ) {
		return (ft_error(INVALID_N_INPUT_FILE, 1));
	} else if ( ac > 1 && ((env->options & ITERATIONS) || (env->options & SIZE)) ) {
		return (ft_error(INVALID_PARAM_COMB, 1));
	}

	std::string **ret = treatInput("1 2 3\n8 5 4\n7 0 6");
	Node *startNode = new Node(3, ret);
	std::cout << "RUNNNN" << '\n';
	run(startNode);
	// if ( read_file(av[ac - 1], input) < 0 )
	// 	return (1);
	// if (!input) {
	// 	// generate_puzzle()
	// } else {
	// 	std::string **ret = treatInput("1 2 3\n4 0 6\n7 8 5");
	// }
	delete [] ret[0];
	delete [] ret[1];
	delete [] ret[2];
	delete [] ret;
	return 0;
}
