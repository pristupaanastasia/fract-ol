# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:40 by smanhack          #+#    #+#              #
#    Updated: 2019/09/20 14:41:07 by smanhack         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRC	= f_cps.c ft_diouxx_up.c ft_printf.c ft_second.c ft_third.c doublf.c ldoublf.c doublf_part_2.c doublf_part_3.c doublf_part_4.c doublf_part_5.c ldoublf_part_2.c ldoublf_part_3.c ldoublf_part_4.c ldoublf_part_5.c ldoublf_part_6.c ft_fourth.c ldoublf_part_7.c ft_rainbow.c bonus_part.c

SRC_LIB = ft_atoi.c ft_lstiter.c ft_putchar.c ft_strcmp.c ft_strmapi.c ft_strtrim.c ft_bzero.c ft_lstmap.c ft_putchar_fd.c ft_strcpy.c ft_strncat.c ft_tolower.c ft_isalnum.c ft_lstnew.c ft_putendl.c ft_strdel.c ft_strncmp.c ft_toupper.c ft_isalpha.c ft_memalloc.c ft_putendl_fd.c ft_strdup.c ft_strncpy.c ft_isascii.c ft_memccpy.c ft_putnbr.c ft_strequ.c ft_strnequ.c ft_isdigit.c ft_memchr.c ft_putnbr_fd.c ft_striter.c ft_strnew.c ft_isprint.c ft_memcmp.c ft_putstr.c ft_striteri.c ft_strnstr.c ft_itoa.c ft_memcpy.c ft_putstr_fd.c ft_strjoin.c ft_strrchr.c ft_lstadd.c ft_memdel.c ft_strcat.c ft_strlcat.c ft_strsplit.c ft_lstdel.c ft_memmove.c ft_strchr.c ft_strlen.c ft_strstr.c ft_lstdelone.c ft_memset.c ft_strclr.c ft_strmap.c ft_strsub.c ft_realloc.c ft_number_of_digits.c ft_itoa_base_ull.c ft_putnbr_endl.c ft_itoa_ll.c ft_strsizeupdata.c ft_strset.c get_next_line.c ft_number_of_word.c ft_freesplit.c ft_itoa_base_size_t.c ft_itoa_base_uintmax_t.c ft_itoa_intmax_t.c ft_itoa_ssize_t.c

SRCS_LIB = $(addprefix ./libft/, $(SRC_LIB))

FLAGS = -Wall -Wextra -Werror

HDR = ../libft.h ft_printf.h

OBJ = $(SRC:%.c=%.o)

OBJ_LIB = $(SRC_LIB:%.c=%.o)

all : $(NAME)

$(NAME) :
	@gcc $(FLAGS) -c $(SRC) $(SRCS_LIB) -I$(HDR)
	@ar rc $(NAME) $(OBJ) $(OBJ_LIB)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_LIB)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re