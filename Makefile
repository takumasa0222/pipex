# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 03:04:25 by tamatsuu          #+#    #+#              #
#    Updated: 2024/10/10 20:46:59 by tamatsuu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
# CC			= clang
#CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror 
SRCS		= ./src/main.c \
./src/init_pipex.c \
./src/pipex.c \
./src/pipex_utils.c \
./src/validation.c \
./src/validation_2.c \
./src/validation_utils.c\
./src/pipex_utils_2.c \
./src/pipex_utils_3.c \
./ft_get_next_line/get_next_line.c \
./ft_get_next_line/get_next_line_utils.c \
./src/init_path.c

OBJS		= $(SRCS:%.c=%.o)
BONUS		= ./bonus/main_bonus.c \
./bonus/init_pipex_bonus.c \
./bonus/pipex_bonus.c \
./bonus/pipex_utils_bonus.c \
./bonus/validation_bonus.c \
./bonus/validation_2_bonus.c \
./bonus/validation_utils_bonus.c\
./bonus/pipex_utils_2_bonus.c \
./bonus/pipex_utils_3_bonus.c \
./ft_get_next_line/get_next_line.c \
./ft_get_next_line/get_next_line_utils.c \
./bonus/init_path_bonus.c
LIB			= ./libft/libft.a
BOBJS		= $(BONUS:%.c=%.o)
ifdef WITH_BONUS_PIPEX
OBJS		= $(BOBJS)
else
OBJS	= $(SRCS:%.c=%.o)
endif
NAME		= pipex
AR		= ar

.PHONY: all clean fclean re norm bonus
.SILENT: all
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C libft
	$(CC) $(OBJS) -Lft -lft -L./libft -g -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g  -c $< -o $@

clean:
	@make clean -C libft
	rm -f $(OBJS) $(BOBJS)
	
fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

bonus:
	@make WITH_BONUS_PIPEX=1


norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(BONUS)
	norminette -R CheckDefine src/*.h bonus/*.h

re: fclean all
