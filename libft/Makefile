CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinc
DEBUGFLAGS = -g3 -gdwarf-3 -O0 -fsanitize=address -fsanitize=undefined
NAME = libft.a
SRC_DIR = src
OBJ_DIR = obj

# Define source files in respective directories
INBOX_SRC_FILES =  

LISTS_SRC_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				  ft_lstmap.c

DLISTS_SRC_FILES = ft_dlst.c ft_dlst_2.c

STRING_SRC_FILES = ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_strjoin.c ft_strlcat.c strdup_safe.c ft_split_cs.c \
	ft_count_strs.c ft_free_strs.c

MEMORY_SRC_FILES = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
				   ft_memmove.c ft_memset.c

CTYPE_SRC_FILES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
				  ft_isprint.c ft_isspace.c

PRINTF_SRC_FILES = helpers.c types.c types_nbr.c ft_printf.c

MATH_SRC_FILES = ft_atoi.c ft_itoa.c ft_strtoll.c

IO_SRC_FILES = ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

# Define directory paths
INBOX_DIR = $(SRC_DIR)/inbox/
LISTS_DIR = $(SRC_DIR)/lists/
DLISTS_DIR = $(SRC_DIR)/dlists/
STRING_DIR = $(SRC_DIR)/string/
MEMORY_DIR = $(SRC_DIR)/memory/
CTYPE_DIR = $(SRC_DIR)/ctype/
PRINTF_DIR = $(SRC_DIR)/printf/
MATH_DIR = $(SRC_DIR)/math/
IO_DIR = $(SRC_DIR)/io/

# Create full paths to source files
INBOX_SRC = $(addprefix $(INBOX_DIR), $(INBOX_SRC_FILES))
LISTS_SRC = $(addprefix $(LISTS_DIR), $(LISTS_SRC_FILES))
DLISTS_SRC = $(addprefix $(DLISTS_DIR), $(DLISTS_SRC_FILES))
STRING_SRC = $(addprefix $(STRING_DIR), $(STRING_SRC_FILES))
MEMORY_SRC = $(addprefix $(MEMORY_DIR), $(MEMORY_SRC_FILES))
CTYPE_SRC = $(addprefix $(CTYPE_DIR), $(CTYPE_SRC_FILES))
PRINTF_SRC = $(addprefix $(PRINTF_DIR), $(PRINTF_SRC_FILES))
MATH_SRC = $(addprefix $(MATH_DIR), $(MATH_SRC_FILES))
IO_SRC = $(addprefix $(IO_DIR), $(IO_SRC_FILES))

# Combine all source files
SRCS = $(INBOX_SRC) $(LISTS_SRC) $(DLISTS_SRC) $(STRING_SRC) $(MEMORY_SRC) \
	   $(CTYPE_SRC) $(PRINTF_SRC) $(MATH_SRC) $(IO_SRC)

# Create object file paths that preserve the directory structure
# $(patsubst pattern,replacement,text)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Create object directories as needed and compile
# $@ is an automatic variable that represents the target of the rule (the .o file being created).
# $(dir x) is a function that extracts the directory part of the file path x.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Debug and release targets
debug: CFLAGS += $(DEBUGFLAGS)
debug: all

release: DEBUGFLAGS =
release: all

.PHONY: all clean fclean re

