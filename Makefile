NAME = minishell

# Directories
SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFT_DIR)/includes

LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lreadline

SRCS = \
	srcs/main.c \
	srcs/read_input.c \
	srcs/run_line.c \
	srcs/builtins/builtins.c \
	srcs/builtins/ft_cd.c \
	srcs/builtins/ft_echo.c \
	srcs/builtins/ft_env.c \
	srcs/builtins/ft_exit.c \
	srcs/builtins/ft_export_print.c \
	srcs/builtins/ft_export_utils.c \
	srcs/builtins/ft_export.c \
	srcs/builtins/ft_pwd.c \
	srcs/builtins/ft_unset.c \
	srcs/env/env_get.c \
	srcs/env/env_init.c \
	srcs/env/env_set.c \
	srcs/exec/child_exec.c \
	srcs/exec/child_exec_utils.c \
	srcs/exec/child_pipe.c \
	srcs/exec/child.c \
	srcs/exec/exec.c \
	srcs/exec/heredoc.c \
	srcs/exec/heredoc_child.c \
	srcs/exec/path.c \
	srcs/exec/redir_apply.c \
	srcs/exec/expand_cmd_args.c \
	srcs/exec/wait.c \
	srcs/expand/expand_escape.c \
	srcs/expand/expand_hd.c \
	srcs/expand/expand_utils.c \
	srcs/expand/expand.c \
	srcs/expand/wildcard_apply.c \
	srcs/expand/wildcard_dir.c \
	srcs/expand/wildcard.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer.c \
	srcs/lexer/token_utils.c \
	srcs/lexer/token.c \
	srcs/parser/parser_helpers.c \
	srcs/parser/parser_list.c \
	srcs/parser/parser_nodes.c \
	srcs/parser/parser_redir.c \
	srcs/parser/parser_sub.c \
	srcs/parser/parser.c \
	srcs/parser/syntax_utils.c \
	srcs/parser/syntax.c \
	srcs/utils/error.c \
	srcs/utils/free.c \
	srcs/utils/signals_heredoc.c \
	srcs/utils/signals.c

RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
MAGENTA = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m
RESET   = \033[0m

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME) finish

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)[MINISHELL] Compiling: $(CYAN)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) --no-print-directory

clean:
	@printf "$(MAGENTA)[MINISHELL] Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean --no-print-directory
	@printf "$(GREEN)[MINISHELL] Cleaned !$(RESET)\n"

fclean: clean
	@printf "$(MAGENTA)[MINISHELL] Cleaning libft and executable...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean --no-print-directory
	@printf "$(GREEN)[MINISHELL] Cleaned !$(RESET)\n"

re: fclean all

finish:
	@printf '$(GREEN)'
	@printf '\n  __  __ _       _     _          _ _ \n'
	@printf ' |  \/  (_)     (_)   | |        | | |\n'
	@printf ' | \  / |_ _ __  _ ___| |__   ___| | |\n'
	@printf ' | |\/| | | |_ \| / __| |_ \ / _ \ | |\n'
	@printf ' | |  | | | | | | \__ \ | | |  __/ | |\n'
	@printf ' |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|\n'
	@printf '$(RESET)\n'
	@printf "\r\033[K✅ $(GREEN)[MINISHELL] Compiled !$(RESET)\n"

.PHONY: all clean fclean re finish