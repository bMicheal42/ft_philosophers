# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmicheal <bmicheal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 10:45:11 by bmicheal          #+#    #+#              #
#    Updated: 2021/02/04 15:51:06 by bmicheal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c utils.c
OBJS			= $(SRCS:.c=.o)

NAME			= philo_one
CFLAGS			 = -Wall -Wextra -Werror -g -I. -O2
all:			$(NAME)

$(NAME):		$(OBJS)
				gcc $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
				rm -rf $(OBJS)

fclean:			clean
				-rm -rf $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re