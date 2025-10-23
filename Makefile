NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes -Ilibft -I/usr/include/readline -fPIE
RM = rm -rf

# Directories
OBJ_DIR = obj
SRC_DIR = src
PIPE_DIR = pipe
TOKEN_DIR = token
INC_DIR = includes
LIBFT_DIR = libft

# Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)

# Readline
READLINE_INC = -I/usr/include/readline
READLINE_LIB = -lreadline

# Source files
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/error.c\
      $(SRC_DIR)/expand.c $(SRC_DIR)/execute.c \
      $(SRC_DIR)/commands.c $(SRC_DIR)/commands2.c $(SRC_DIR)/commands2_utils.c \
      $(SRC_DIR)/export.c $(SRC_DIR)/export_utils.c \
      $(SRC_DIR)/signals.c $(SRC_DIR)/parsing.c $(SRC_DIR)/redirection.c \
      $(SRC_DIR)/redirection_utils.c $(SRC_DIR)/redirection_handlers.c \
      $(SRC_DIR)/heredoc.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/signals2.c\
      $(SRC_DIR)/handle_dollar.c \
      $(PIPE_DIR)/pipe.c $(PIPE_DIR)/path.c $(PIPE_DIR)/pipe_utils.c $(PIPE_DIR)/pipe_execution.c\
      $(TOKEN_DIR)/tokenize.c $(TOKEN_DIR)/tokenize_helpers.c \
      $(TOKEN_DIR)/token_utils.c \
      $(TOKEN_DIR)/token_count.c $(TOKEN_DIR)/token_length.c \
      $(TOKEN_DIR)/token_create.c $(SRC_DIR)/expand_utils.c $(SRC_DIR)/expand_utils2.c

# Object files in obj/ (mirror folder structure)
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Include paths
CFLAGS += -I$(INC_DIR) -I$(LIBFT_INC) $(READLINE_INC)

# Link flags
LDFLAGS = $(LIBFT) $(READLINE_LIB)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

# Rule to build .o in obj/ keeping subfolder structure
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
