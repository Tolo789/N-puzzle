NAME = n-puzzle

SDIR = ./

SRC = 	$(SDIR)main.cpp \
		$(SDIR)Node.class.cpp \
		$(SDIR)Point.class.cpp \
		$(SDIR)Env.class.cpp \
		$(SDIR)options_handling.cpp \
		$(SDIR)treat_input.cpp \
		$(SDIR)tools.cpp \
		$(SDIR)error.cpp \
		$(SDIR)astar.cpp

OBJ = $(SRC:.cpp=.o)

ALL = $(NAME)

CFLAGS = -Wall -Wextra #-Werror

CC = clang++

all: $(ALL)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "				$(NAME) created"

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I .

clean:
	@/bin/rm -f $(OBJ)
	@echo "				All project's .o deleted"

fclean: clean
	@/bin/rm -f $(ALL)
	@echo "				All exec(s) deleted"

re: fclean all

.PHONY: all lib clean fclean re
