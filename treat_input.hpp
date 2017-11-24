#ifndef TREAT_INPUT_HPP
# define TREAT_INPUT_HPP

typedef struct	s_treatInput {
	size_t			size;
	std::string		**ret;
}				t_treatInput;

int		treatInput(t_treatInput *retTreatinput, std::string input);

#endif
