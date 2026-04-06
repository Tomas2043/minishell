# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darafael <darafael@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 14:06:56 by toandrad          #+#    #+#              #
#    Updated: 2026/04/06 13:13:26 by darafael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ift_printf

AR = ar rcs

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Emojis
COMPILE_EMOJI = 🔨
LIBRARY_EMOJI = 📚
CLEAN_EMOJI = 🧹
SUCCESS_EMOJI = ✅
ROCKET_EMOJI = 🚀

SRCS = \
			ft_is/ft_isalpha.c ft_is/ft_isdigit.c ft_is/ft_isalnum.c ft_is/ft_isascii.c ft_is/ft_isprint.c \
			ft_lsts/ft_lstadd_back.c ft_lsts/ft_lstadd_front.c ft_lsts/ft_lstclear.c ft_lsts/ft_lstdelone.c \
			ft_lsts/ft_lstiter.c ft_lsts/ft_lstlast.c ft_lsts/ft_lstmap.c ft_lsts/ft_lstnew.c ft_lsts/ft_lstsize.c \
			ft_to/ft_itoa.c ft_to/ft_toupper.c ft_to/ft_tolower.c ft_to/ft_atoi.c \
			ft_str/ft_strchr.c ft_str/ft_strrchr.c ft_str/ft_strncmp.c ft_str/ft_split.c \
			ft_str/ft_strlen.c ft_str/ft_strlcpy.c ft_str/ft_strlcat.c ft_str/ft_strnstr.c \
			ft_str/ft_striteri.c ft_str/ft_strdup.c ft_str/ft_substr.c ft_str/ft_strjoin.c \
			ft_str/ft_strtrim.c ft_str/ft_strmapi.c	ft_str/ft_strcmp.c \
			ft_mem/ft_memset.c ft_mem/ft_bzero.c ft_mem/ft_memcpy.c ft_mem/ft_memmove.c \
			ft_mem/ft_memchr.c ft_mem/ft_memcmp.c ft_mem/ft_calloc.c \
			ft_put/ft_putchar_fd.c ft_put/ft_putstr_fd.c ft_put/ft_putendl_fd.c ft_put/ft_putnbr_fd.c \
			get_next_line/get_next_line.c

OBJSDIR = objects
OBJS = $(addprefix $(OBJSDIR)/, $(notdir $(SRCS:.c=.o)))

all: banner $(NAME)

$(NAME): $(OBJS)
	@echo "$(LIBRARY_EMOJI) $(CYAN)Creating library $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(SUCCESS_EMOJI) $(GREEN)Library $(NAME) created successfully!$(RESET)"

# Create objects directory
$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

# Compilation rules for each directory
$(OBJSDIR)/%.o: ft_is/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_to/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_str/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_mem/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_put/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_lsts/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_printf/%.c ft_printf/ft_printf.h libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: ft_printf/utils/%.c ft_printf/ft_printf.h libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)/%.o: get_next_line/%.c libft.h | $(OBJSDIR)
	@echo "$(COMPILE_EMOJI) $(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CLEAN_EMOJI) $(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJSDIR)
	@echo "$(SUCCESS_EMOJI) $(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(CLEAN_EMOJI) $(RED)Removing library $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(SUCCESS_EMOJI) $(GREEN)Library removed!$(RESET)"

re: fclean all
	@echo "$(ROCKET_EMOJI) $(PURPLE)Rebuild complete!$(RESET)"

.PHONY: all banner clean fclean re
