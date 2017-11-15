#ifndef ERROR_HPP
# define ERROR_HPP

# define UNKNOWN_OPTION "Error: unknown option."
# define ONLY_ONE_HEUR "Error: only one heuristic can be set."
# define INVALID_HEUR "Error: invalid heuristic type."
# define INVALID_FILENAME "Error: invalid filename."
# define INVALID_PARAM_COMB "Error: invalid parameters combinasion."
# define INVALID_OPTION_VALUE "Error: an options value is invalid."

int		ft_error(std::string const type, int const ret);

#endif
