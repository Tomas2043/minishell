# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/17 11:50:14 by toandrad          #+#    #+#              #
#    Updated: 2026/04/16 14:44:39 by toandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN		= \033[0;32m
YELLOW		= \033[1;33m
BLUE		= \033[0;34m
RED			= \033[0;31m
BOLD		= \033[1m
RESET		= \033[0m

SRCDIR = src
OBJSDIR = objects
INCDIR = inc
LIBFT_DIR = libft
VPATH = $(SRCDIR) $(SRCDIR)/env $(SRCDIR)/tokenizer $(SRCDIR)/utilitarians $(SRCDIR)/exec
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE_FLAGS = -I$(INCDIR) -I$(LIBFT_DIR)

SRCS = main.c \
	   env_helpers.c \
	   env_init.c \
	   env_utils.c \
	   syntax_check.c \
	   token_building.c \
	   tokenizer_count.c \
	   tokenizer_utils.c \
	   tokenizer_utils2.c \
	   tokenizer_utils3.c \
	   tokenizer_words.c \
	   utils.c \
		 path_resolution.c \
		 redirections.c \
		 builtins.c \
		 builtins2.c \
		 executor.c \
		 executor_helpers.c \
		 pipes.c \
		 pipe_helpers.c \
		 

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

# ================================== RULES ================================== #

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)🛠️  Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ libft built successfully.$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)🛠️  Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)✅ Executable created: $(BLUE)$(NAME)$(RESET)"

$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@rm -rf $(OBJSDIR)
	@echo "$(RED)🧹 Object files deleted$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(RED)🗑️  All generated files deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re