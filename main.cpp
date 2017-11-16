#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Node.class.hpp"
#include "Env.class.hpp"
#include "options_handling.hpp"
#include "astar.hpp"
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

int				main(int ac, char **av) {
	std::string		*input;

	t_puzzle p = {0, 0};
	input = NULL;
	// if (ac == 1) {
		// return (usage(av[0]));
	if ( get_options(&ac, av) ) {
		return (1);
	} else if ( Env::options & HELP ) {
		return (usage(av[0]));
	} else if ( ac > 2 ) {
		return (ft_error(INVALID_N_INPUT_FILE, 1));
	} else if ( ac > 1 && ((Env::options & ITERATIONS) || (Env::options & SIZE)) ) {
		return (ft_error(INVALID_PARAM_COMB, 1));
	}

	// std::string **ret = treatInput("5 4 2\n7 0 6\n3 8 1");
	std::string **ret = treatInput("1 2 3\n8 4 0\n7 6 5");
	Node *startNode = new Node(3, ret);
	std::cout << " ### RUN A-STAR #########################" << '\n';
	runAStar(startNode);
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
