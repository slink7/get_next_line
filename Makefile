# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scambier <scambier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 20:48:44 by scambier          #+#    #+#              #
#    Updated: 2023/11/19 16:21:41 by scambier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRC = \
	get_next_line.c\
	main.c

OBJ = $(addsuffix .o, $(notdir $(basename $(SRC))))
OBJ_BONUS = $(addsuffix .o, $(notdir $(basename $(SRC_BONUS))))

CFLAGS = -Wall -Werror -Wextra -g3

default : all

all : $(NAME)

%.o : %.c
	cc $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	cc -o $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ) $(OBJ_BONUS) || true

fclean : clean
	rm $(NAME) || true

re : fclean all


.PHONY : re fclean clean all default