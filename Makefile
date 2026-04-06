# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/17 11:50:14 by toandrad          #+#    #+#              #
#    Updated: 2026/04/06 12:06:27 by toandrad         ###   ########.fr        #
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
LIBFT = libft/libft.a
VPATH = $(SRCDIR) $(SRCDIR)/env $(SRCDIR)/exec

SRCS = main.c env_helpers.c env_init.c env_utils.c path_helpers.c path_resolution.c

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

# ================================== RULES ================================== #

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)🛠️  Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✅ libft built successfully.$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)🛠️  Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INCDIR) -I$(LIBFT_DIR) -o $(NAME) -lreadline
	@echo "$(GREEN)✅ Executable created: $(BLUE)$(NAME)$(RESET)"

$(OBJSDIR)/%.o: %.c | $(OBJSDIR)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

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