# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/16 15:24:05 by rcargou           #+#    #+#              #
#    Updated: 2015/10/16 16:32:58 by rcargou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = librcmath.a

SRC = rcm_dotproduct.c rcm_rotmat.c rcm_vecnormalise.c rcm_vecsquarelenght.c rcm_2dequation.c \
	rcm_crossproduct.c  rcm_min.c \
	rcm_vecscalarfactor.c rcm_vecsum.c rcm_fabs.c \
	rcm_vecneg.c  rcm_vecnorme.c rcm_sqrt.c rcm_vecsub.c rcm_vecproject.c rcm_identitymat.c \
	rcm_multmat.c rcm_projectmat.c rcm_transmat.c rcm_addmat.c rcm_mulmatscalar.c rcm_veceq.c \
	rcm_setpoint.c rcm_scalemat.c rcm_rotmatrice.c

OBJ = $(SRC:.c=.o)

All : $(NAME)

$(NAME) :
	@gcc -c $(SRC) rc_math.h
	@ar rc $(NAME) $(OBJ)

clean :
	@rm $(OBJ)

fclean : 
	@rm -rf $(NAME)

re : fclean All
