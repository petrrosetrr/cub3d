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
			./gnl/get_next_line_utils.c ./raycaster/raycaster.c \
			 ./map_validation/ft_validation.c
NAME    =   cub3d.out
HEAD	=	cub3d.h
LIBFT	=	./libft/libft.a
OBJS    =   $(SRCS:.c=.o)
GCC     =   gcc -Wall -Wextra -Werror -g
RM      =   rm -f
C       =   -c
O       =   -o
#-Lmlx -lmlx -framework OpenGL -framework AppKit -lm
.PHONY:		all clean fclean re

.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)
all:		$(NAME)

$(NAME):    $(OBJS) $(HEAD) $(MLX)
			make -C ./libft
			make -C ./mlx
			cp ./mlx/libmlx.dylib .
			$(GCC) $(OBJS) ./libft/libft.a libmlx.dylib -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C ./libft
			make clean -C ./mlx

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft

re:         fclean all