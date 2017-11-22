#ifndef ERROR_HPP
# define ERROR_HPP

# define UNKNOWN_OPTION "Error: unknown option."
# define ONLY_ONE_HEUR "Error: only one heuristic can be set."
# define INVALID_HEUR "Error: invalid heuristic type."
# define INVALID_FILENAME "Error: invalid filename."
# define INVALID_PARAM_COMB "Error: invalid parameters combinasion."
# define INVALID_OPTION_VALUE "Error: an options value is invalid."
# define INVALID_N_INPUT_FILE "Error: too many input file."
# define INVALID_SIZE "Error: invalid size value."
# define INVALID_NONUM_CHAR "Error: not numeric char in puzzle."
# define INVALID_LINE_FORMAT "Error: bad line format."
# define INVALID_PUZZLE_SIZE "Error: size and puzzle don't match."
# define BAD_MEMBER "Error: a member is missing or found a unknown member in the puzzle."

int		ft_error(std::string const type, int const ret);

#endif
