#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Node.class.hpp"
#include "Env.class.hpp"
#include "options_handling.hpp"
#include "error.hpp"
#include "treat_input.hpp"
#include "astar.hpp"

static int	read_file(char const *filename, std::string *input) {
	std::fstream		file;
	std::string			line;
	std::stringstream	sstream;

	if ( !filename ) {
		return ( 0 );
	} else {
		file.open( filename, std::ios::in );
		if ( file.is_open() ) {
			while ( getline(file, line) ) {
				sstream << line << std::endl;
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
	std::cout << "  -" << HELP_CHAR << " : display help menu and exits." << std::endl;
	std::cout << "  -" << SLOW_PRINT_CHAR << " <speed> (min: 1, max: 5000) : display slowly the solution." << std::endl;
	std::cout << "  -" << GREEDY_CHAR << " : activate greedy search." << std::endl;
	std::cout << "  -" << HEUR_CHAR << " <heuristic> : (default: man)" << std::endl;
	std::cout << "    heuristics:" << std::endl;
	std::cout << "      '" << HEUR_MAN_STR << "' : Manhattan" << std::endl;
	std::cout << "      '" << HEUR_2_STR << "' : Manhattan with linear conflict" << std::endl;
	std::cout << "      '" << HEUR_3_STR << "' : Misplaced tiles" << std::endl;
	std::cout << "      '" << HEUR_4_STR << "' : Manhattan with linear conflict and misplaced tiles" << std::endl;
	std::cout << std::endl << "  /* If you don't provide any input file */" << std::endl;
	std::cout << "  -" << SIZE_CHAR << " <size> (min: 2, max: 100, default: 3): set a size for a random generated puzzle" << std::endl;
	std::cout << "  -" << ITERATIONS_CHAR << " <iterations> (default: 10000): set a number of iterations for a random generated puzzle" << std::endl;
	return (1);
}

int				main(int ac, char **av) {
	std::string		input;
	t_treatInput	retTreatinput;
	Node			*startNode;

	if ( get_options(&ac, av) ) {
		return (1);
	} else if ( Env::options & HELP ) {
		return (usage(av[0]));
	} else if ( ac > 2 ) {
		return (ft_error(INVALID_N_INPUT_FILE, 1));
	} else if ( ac > 1 && ((Env::options & ITERATIONS) || (Env::options & SIZE)) ) {
		return (ft_error(INVALID_PARAM_COMB, 1));
	} else if ( ac == 2 && (read_file(av[ac - 1], &input) < 0 || input.length() == 0) ) {
		return (ft_error(INVALID_INPUT_FILE, 1));
	} else if ( ac == 1 ) {
		startNode = new Node();
	} else {
		if (treatInput(&retTreatinput, input)) {
			return (1);
		}
		try {
			startNode = new Node(retTreatinput.ret);
			if ( !Node::isSolvable(*startNode) ) {
				return (ft_error(NOT_SOLVABLE, 1));
			}
		}
		catch (Node::MissingMemberException & e) {
			return (ft_error(e.what(), 1));
		}
	}
	runAStar(startNode);
	std::cout << "Total number of states: " << Env::totalNumberOfStates << std::endl;
	std::cout << "Max number of states: " << Env::maxNumberOfState << std::endl;
	std::cout << "Number of move: " << Env::numberOfMove << std::endl;

	return 0;
}
