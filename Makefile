CXX := cc
FLAGS := -Wall -Wextra -Werror -pedantic
NAME := vbc
SRC := main.c vbc.c
OBJ_DIR := obj/
OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(FLAGS) $^ -o $@

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) $^ -c -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
