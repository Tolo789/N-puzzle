#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Map.class.hpp"
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
	std::cout << "  -h <heuristic>:" << std::endl;
	std::cout << "    heuristics:" << std::endl;
	std::cout << "      '" << HEUR_MAN_STR << "' : Manhattan" << std::endl;
	std::cout << "      '" << HEUR_2_STR << "' : ..." << std::endl;
	std::cout << "      '" << HEUR_3_STR << "' : ..." << std::endl;
	std::cout << "  /* If you don't provide any input file */" << std::endl;
	std::cout << "  -s <size> (Default: 3): set a size for a random generated puzzle" << std::endl;
	std::cout << "  -i <iterations> (Default: 10000): set a number of iterations for a random generated puzzle" << std::endl;
	return (1);
}

int				main(int ac, char **av) {
	Env				*env;
	std::string		*input;

	t_puzzle p = {0, 0};
	env = new Env();
	input = NULL;
	if (ac == 1) {
		return (usage(av[0]));
	} else if ( get_options(env, &ac, av) ) {
		return (1);
	} else if ( ac > 1 && ((env->options & ITERATIONS) || (env->options & SIZE)) ) {
		return (ft_error(INVALID_PARAM_COMB, 1));
	}
	std::cout << "RUNNNN" << '\n';
	// if ( read_file(av[ac - 1], input) < 0 )
	// 	return (1);
	// if (!input) {
	// 	// generate_puzzle()
	// } else {
	// 	std::string **ret = treatInput("1 2 3\n4 0 6\n7 8 5");
	// }
	// Map *mapOne = new Map(3, ret);
	//
	// // find specific point in map
	// Point tmp = mapOne->points.find(4)->second;
	// std::cout << std::endl << "Test for find in map:" << std::endl;
	// std::cout << tmp.toString();
	// // test if map is well linked with array
	// std::cout << mapOne->array[tmp.y_current][tmp.x_current] << std::endl;
	//
	// // iter over all points
	// std::cout << std::endl << "Printing all points" << std::endl;
	// std::map<size_t, Point>::iterator it;
	// // ft_e(*mapOne);
	// for (it = mapOne->points.begin(); it != mapOne->points.end(); it++) {
	// 	std::cout << (it->second).toString() << std::endl;
	// }
	//
	// /*
	// 	do things
	// 	.....
	// */
	// delete [] ret[0];
	// delete [] ret[1];
	// delete [] ret[2];
	// delete [] ret;
	return 0;
}
