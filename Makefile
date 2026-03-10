NAME = diff_eq
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LFLAGS = -lm

INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs

SRC_FILES = main.c \
			euler_explicit.c \
			euler_implicit.c \
			crank_nicolson.c \
			utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCS = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re