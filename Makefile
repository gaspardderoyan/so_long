CC = cc
CFLAGS = -Wall -Wextra -Werror -Inc -Ilibft/inc
DEBUGFLAGS = -g3 -fsanitize=address -fsanitize=undefined -fsanitize=alignment

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = so_long

SRCS = main.c

# $(text:pattern=replacement)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean libft re

################################################################################
# Main Build Targets
################################################################################

all: $(NAME)

# Build the main executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(DEBUGFLAGS) -o $(NAME) -L$(LIBFT_DIR) -lft 

# Compile the object files for main sources
# TODO use if statement > -p
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) # @ so not printed
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

################################################################################
# Helper Targets (clean, fclean, re)
################################################################################

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) debug

# Clean object files and libft's objs
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

# TODO clean test executables
# + executables
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(TEST_EXES)

# Rebuild the project
re: fclean all
