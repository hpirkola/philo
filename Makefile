# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 14:05:00 by hpirkola          #+#    #+#              #
#    Updated: 2025/02/13 14:41:14 by hpirkola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

GREEN =  \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
ORANGE = \e[1m\e[38;5;202m
RESET = \033[0;39m

COMPILED = echo "🗃️  $(ORANGE)Files compiled!$(RESET)"
ALL_READY = echo "🍴 $(GREEN)All done! Philosophers are ready to dine!$(RESET)"
CLEANING = echo "🫧 $(BLUE)Cleaning files...$(RESET)"
CLEANED = echo "🫧 $(BLUE)All object files cleaned!$(RESET)"
PURGE = echo "🧽 $(PURPLE)Deep cleaning files...$(RESET)"
PURGED = echo "🧽 $(PURPLE)All cleaned!$(RESET)"
REDO = echo "🛠️ $(RED)Program rebuilt!$(RESET)"

SRC = ./src/main.c ./src/threads.c ./src/activities.c \
		./src/philo.c ./src/init.c ./src/ft_atoi.c \
		./src/utils.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pthread -g3 #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $@
	@$(COMPILED)
	@$(ALL_READY)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@$(CLEANING)
	@rm -f $(OBJ)
	@$(CLEANED)
	
fclean: clean
	@$(PURGE)
	@rm -f $(NAME)
	@$(PURGED)

re: fclean all
	@$(REDO)

.PHONY: all clean fclean re
