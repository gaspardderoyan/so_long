CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Imlx

SRC_DIR = src/core
OBJ_DIR = obj

LIBFT_DIR = libft
LIBFT= $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a

NAME = so_long

SRCS = $(SRC_DIR)/main.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Detect OS
UNAME_S := $(shell uname -s)

# OS-specific linking flags
ifeq ($(UNAME_S),Darwin)
	# macOS
	LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	# Linux
	LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif

.PHONY: all clean fclean libft re

################################################################################
# Main Build Targets
################################################################################

all: $(NAME)

# Build the main executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(DEBUGFLAGS) -o $(NAME) $(LFLAGS) 

# Compile the object files for main sources
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) # @ so not printed
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

################################################################################
# Helper Targets (clean, fclean, re)
################################################################################

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) 

# Build mlx
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Clean object files and libft's objs
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	# Only run mlx clean if Makefile.gen exists (prevents error on fresh clone)
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild the project
re: fclean all
