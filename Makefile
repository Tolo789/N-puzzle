NAME = n-puzzle

SDIR = ./

SRC =

OBJ = $(SRC:.cpp=.o)

ALL = $(NAME)

CFLAGS = -Wall -Wextra -Werror

CC = clang++

all: $(ALL)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "				$(NAME) created"

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@echo "				All project's .o deleted"

fclean: clean
	@/bin/rm -f $(ALL)
	@echo "				All exec(s) deleted"

re: fclean all

.PHONY: all lib clean fclean re
