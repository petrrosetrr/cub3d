# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalease <jalease@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 19:04:38 by jalease           #+#    #+#              #
#    Updated: 2020/11/22 19:16:01 by jalease          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c ./parser/ft_parser.c ./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c
			 #./map_validation.c
NAME    =   cub3d.out
HEAD	=	cub3d.h
LIBFT	=	./libft/libft.a
OBJS    =   $(SRCS:.c=.o)
GCC     =   gcc -Wall -Wextra -Werror -g
RM      =   rm -f
C       =   -c
O       =   -o

.PHONY:		all clean fclean re

.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)
all:		$(NAME)

$(NAME):    $(OBJS) $(HEAD)
			make -C ./libft
			$(GCC) $(OBJS) ./libft/libft.a -o $(NAME)
clean:
			$(RM) $(OBJS)
			make clean -C ./libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft

re:         fclean all