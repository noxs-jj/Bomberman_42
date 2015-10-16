# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/16 15:01:44 by rcargou           #+#    #+#              #
#    Updated: 2015/01/17 02:30:33 by rcargou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcolor.a

SRC = color_add.c color_setbright.c color_getcomp.c color_diff.c color_average.c

OBJ = $(SRC:.c=.o)

TILD = $(SRC:.c=.c~)

All : $(NAME)

$(NAME) :
	@gcc -c $(SRC) color.h
	@ar rc $(NAME) $(OBJ)

clean :
	@rm -rf $(OBJ) $(TILD)

fclean : clean
	@rm $(NAME)

re : fclean All
