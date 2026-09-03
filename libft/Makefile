NAME = libft.a 

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar

RM = rm -rf

OBJDIR = obj

SRC = src/char/ft_isalnum.c \
	src/char/ft_isalpha.c \
	src/char/ft_isascii.c \
	src/char/ft_isdigit.c \
	src/char/ft_isprint.c \
	src/char/ft_split.c \
	src/char/ft_tolower.c \
	src/char/ft_toupper.c \
	src/conv/ft_atoi.c \
	src/conv/ft_itoa.c \
	src/fd/ft_putchar_fd.c \
	src/fd/ft_putendl_fd.c \
	src/fd/ft_putnbr_fd.c \
	src/fd/ft_putstr_fd.c \
	src/gnl/get_next_line.c \
	src/lst/ft_lstadd_back.c \
	src/lst/ft_lstadd_front.c \
	src/lst/ft_lstclear.c \
	src/lst/ft_lstdelone.c \
	src/lst/ft_lstiter.c \
	src/lst/ft_lstlast.c \
	src/lst/ft_lstmap.c \
	src/lst/ft_lstnew.c \
	src/lst/ft_lstsize.c \
	src/mem/ft_bzero.c \
	src/mem/ft_calloc.c \
	src/mem/ft_memchr.c \
	src/mem/ft_memcmp.c \
	src/mem/ft_memcpy.c \
	src/mem/ft_memmove.c \
	src/mem/ft_memset.c \
	src/printf/ft_printf.c \
	src/printf/ft_printf_utils.c \
	src/str/ft_strchr.c \
	src/str/ft_strdup.c \
	src/str/ft_striteri.c \
	src/str/ft_strjoin.c \
	src/str/ft_strlcat.c \
	src/str/ft_strlcpy.c \
	src/str/ft_strlen.c \
	src/str/ft_strmapi.c \
	src/str/ft_strncmp.c \
	src/str/ft_strndup.c \
	src/str/ft_strnstr.c \
	src/str/ft_strrchr.c \
	src/str/ft_strtrim.c \
	src/str/ft_substr.c

OBJ = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))

RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m
RESET   = \033[0m

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@printf "\r${BLUE}[LIBFT] Compiling: $(CYAN)$<$(RESET)"
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

${NAME}: ${OBJ}
	@printf "\r\033[K${BLUE}[LIBFT] Compiling libft...${RESET}\n"
	@$(AR) rcs ${NAME} ${OBJ} >/dev/null 2>&1
	@printf "\r\033[K✅ ${GREEN}[LIBFT] Compiled !${RESET}\n"

clean:
	@printf "${MAGENTA}[LIBFT] Cleaning .o files...${RESET}\n"
	@$(RM) $(OBJDIR)
	@printf "${GREEN}[LIBFT] .o files cleaned!${RESET}\n"

fclean: clean
	@printf "${MAGENTA}[LIBFT] Cleaning archive...${RESET}\n"
	@$(RM) $(NAME)
	@printf "${GREEN}[LIBFT] Archive cleaned!${RESET}\n"

re: fclean all

.PHONY: all clean fclean re