# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 11:16:23 by ehedeman          #+#    #+#              #
#    Updated: 2024/06/06 15:54:14 by ehedeman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c				\
		assign_data.c		\
		input_check.c		\
		main_utils.c		\
		philo_actions_u.c	\
		philo_actions.c		\
		philo_forks.c		\
		philo_timestamps.c	\
		philo_wait.c		\
		philo.c				\
		threads_init.c

INCL = philo.h

OBJS = $(SRC:.c=.o)
OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc
CFLAGS = -Werror -Wall -Wextra -g #-fsanitize=address -fno-omit-frame-pointer 
PTHREADS = -pthreads

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: $(NAME) #n

$(NAME): $(OBJS_PREFIXED)
	@$(CC) $(CFLAGS) $(PTHREADS) $(OBJS_PREFIXED) -o $(NAME)

$(OBJS_DIR)%.o : %.c $(INCL)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)Removed object Files\n$(NC)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)Removed binary\n$(NC)"

re: fclean all
	@printf "$(GREEN)Created binary.\n$(NC)"
e: re
	./$(NAME) 3 2 2 2 2

leaks:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes ./philo 4 310 200 100

threads:
	valgrind --tool=helgrind ./philo 3 310 100 100
	
n:
	@printf "$(GREEN)"
	@norminette $(SRC) $(INCL)
	@printf "$(NC)"

.PHONY: all clean fclean re e leaks threads n