# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 03:04:25 by tamatsuu          #+#    #+#              #
#    Updated: 2024/09/28 04:31:46 by tamatsuu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#CC			= cc
CC			= clang
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
./ft_get_next_line/get_next_line.c \
./ft_get_next_line/get_next_line_utils.c \
./src/init_path.c


OBJS		= $(SRCS:%.c=%.o)
BONUS		=
LIB			= ./libft/libft.a
BOBJS		= $(BONUS:%.c=%.o)
NAME		= pipex
AR		= ar

.PHONY: all clean fclean re norm bonus
.SILENT: all
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C libft
	$(CC) $(OBJS) -Lft -lft -L./libft -g -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g -O0 -c $< -o $@

clean:
	@make clean -C libft
	rm -f $(OBJS) $(BOBJS)
	
fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

#bonus: $(BOBJS)
#	@make -C libft
#	@cp $(LIB) $(NAME)
#	$(AR) rcs $(NAME) $(BOBJS)

#$(BOBJS): $(BONUS)
#	$(CC) $(CFLAGS) -c $(BONUS)

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckDefine *.h

re: fclean all
