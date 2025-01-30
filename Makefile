# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 14:05:00 by hpirkola          #+#    #+#              #
#    Updated: 2025/01/30 11:48:03 by hpirkola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = ./src/main.c ./src/threads.c ./src/activities.c \
		./src/philo.c ./src/init.c ./src/ft_atoi.c \
		./src/utils.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
