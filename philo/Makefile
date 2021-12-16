# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adidion <adidion@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 16:34:36 by adidion           #+#    #+#              #
#    Updated: 2021/12/11 16:44:34 by adidion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

NAME =	philo

SRCS =	main.c\
		ft_error_management.c\
		libft_1.c\
		ft_analyse_arguments.c\
		ft_create_thread.c\
		ft_time.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS) $(OB)

fclean: clean
	rm -f $(NAME) $(OB)

re: fclean all

.PHONY: re bonus clean fclean all

