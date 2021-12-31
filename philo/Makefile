# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adidion <adidion@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 16:34:36 by adidion           #+#    #+#              #
#    Updated: 2021/12/31 11:03:38 by adidion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

NAME =	philo

SRCS =	main.c\
		ft_error_management.c\
		libft_1.c\
		ft_analyse_arguments.c\
		ft_create_thread.c\
		ft_time.c\
		libft_2.c\
		ft_deal_end.c\
		ft_routine.c\

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

