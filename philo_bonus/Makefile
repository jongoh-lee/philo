CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER) -fsanitize=address
NAME = philo_bonus

SRC_FILES = 00.main_bonus.c \
		01.parse_bonus.c \
		02.err_bonus.c \
		03.hooks_bonus.c \
		04.modules_bonus.c \
		05.modules_bonus.c
OBJ_DIR = objs
HEADER = .
SRC_DIR = .
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all : $(NAME)

$(NAME) : $(OBJS_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean :
	rm -rf $(OBJ_DIR)

fclean :
	rm -rf $(NAME) $(OBJ_DIR)

re : clean all

.PHONY: all clean fclean re
