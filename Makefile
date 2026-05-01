NAME        = minishell

# Directories
SRCDIR      = src
OBJDIR      = obj
INCDIR      = includes
LIBFT_DIR   = libft

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFT_DIR) -g3
LDFLAGS     = -L$(LIBFT_DIR)
LIBS        = $(LIBFT_DIR)/libft.a -lreadline

# Colors
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
MAGENTA = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m
RESET   = \033[0m

# Sources
SRC_FILES = \
	main.c \
	builtins/builtins.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_export_args.c \
	builtins/ft_export_utils.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	env/create_env.c \
	env/env.c \
	exec/exec_pipes.c \
	exec/heredoc.c \
	exec/heredoc_utils.c \
	exec/path.c \
	exec/pipeline.c \
	exec/pipeline_utils.c \
	exec/process.c \
	exec/redirect.c \
	parsing/clean.c \
	parsing/cmd_builder.c \
	parsing/ft_expand.c \
	parsing/lexer.c \
	parsing/lexer_utils.c \
	parsing/parser.c \
	parsing/parser_utils.c \
	parsing/quotes.c \
	parsing/redir_init.c \
	parsing/redir_parser.c \
	parsing/syntax.c \
	parsing/tokenize.c \
	utils/error.c \
	utils/free.c \
	utils/ft_strcmp.c \
	utils/signal.c

SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(SRC_FILES:%.c=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(NAME) finish

$(NAME): $(LIBFT_DIR)/libft.a $(OBJ)
	@printf "\r\033[K🟡 $(YELLOW)[MINISHELL] Compiling minishell...$(RESET)\n"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@printf "\r\033[K✅ $(GREEN)[MINISHELL] Compiled !$(RESET)\n"

$(LIBFT_DIR)/libft.a:
	@make -s -C $(LIBFT_DIR) --no-print-directory

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r🟡 $(MAGENTA)[COMPILING📦] $<$(RESET) \033[K"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	@printf "🟡 $(MAGENTA)[CLEANING🧹] minishell object files...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@make -s -C $(LIBFT_DIR) clean --no-print-directory
	@printf "✅ $(GREEN)[CLEANED🧹]$(RESET)\n"

fclean: clean
	@printf "🟡 $(MAGENTA)[CLEANING🧹] libft and executable...$(RESET)\n"
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean --no-print-directory
	@printf "✅ $(GREEN)[CLEANED🧹]$(RESET)\n"

re: fclean all

finish:
	@printf '$(WHITE)'
	@printf '\n  __  __ _       _     _          _ _ \n'
	@printf ' |  \/  (_)     (_)   | |        | | |\n'
	@printf ' | \  / |_ _ __  _ ___| |__   ___| | |\n'
	@printf ' | |\/| | | |_ \| / __| |_ \ / _ \ | |\n'
	@printf ' | |  | | | | | | \__ \ | | |  __/ | |\n'
	@printf ' |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|\n'
	@printf '$(RESET)\n'

.PHONY: all clean fclean re finish