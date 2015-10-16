#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 18:16:58 by rcargou           #+#    #+#              #
#    Updated: 2015/09/04 14:12:11 by rcargou          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = ft_memdel.c ft_putnbr_fd.c  ft_strdel.c ft_strmapi.c ft_strsplit.c ft_isdigit.c ft_isprint.c ft_memmove.c ft_putstr.c ft_strdup.c ft_strncat.c ft_strstr.c ft_itoa.c ft_memset.c ft_putstr_fd.c  ft_strequ.c\
 ft_strncmp.c ft_strsub.c ft_atoi.c  ft_memalloc.c ft_putchar.c ft_strcat.c ft_striter.c ft_strncpy.c ft_strtrim.c ft_bzero.c ft_memccpy.c ft_putchar_fd.c   ft_strchr.c ft_strjoin.c ft_strnequ.c ft_tolower.c ft_isalnum.c ft_memchr.c ft_putendl.c ft_strclr.c ft_strlcat.c ft_strnew.c ft_toupper.c ft_isalpha.c ft_memcmp.c ft_putendl_fd.c ft_strcmp.c ft_strlen.c ft_strnstr.c  ft_isascii.c ft_memcpy.c ft_putnbr.c ft_strcpy.c ft_strmap.c ft_strrchr.c ft_striteri.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strerase.c \
ft_strnchr.c ft_abs.c ft_pow.c ft_bintodec.c ft_backchrfils.c ft_dectobin.c ft_strrev.c \
ft_strbchr.c ft_lstswap.c ft_lstsort.c ft_lstmove.c ft_lstinsert.c ft_lstsup.c ft_putnbrbase.c ft_nbrlenbase.c ft_uputnbrbase.c ft_getoptions.c ft_tabstrlen.c ft_atof.c \
ft_newstrc.c ft_freetab.c ft_newstrchr.c ft_lstinsertsort.c ft_lstcpynew.c ft_lstlen.c \
ft_lstfind.c ft_strstrsplit.c ft_strsplit_whitespaces.c get_next_line.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	gcc -Wall -Wextra -Werror -c $(SRC) libft.h
	@@ar rc libft.a $(OBJ)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
