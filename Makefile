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

SRCS	=	main.c \
 			parser/ft_parser.c \
 			parser/utils.c \
 			parser/utils2.c \
 			parser/utils3.c \
 			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			raycaster/raycaster.c \
			map_validation/ft_validation.c \
			map_validation/utils.c \
			map_validation/utils2.c \
			raycaster/utils.c \
			raycaster/utils_2.c \
			raycaster/intersections.c \
			raycaster/player.c \
			raycaster/map.c \
			raycaster/sprites.c \
			raycaster/textures.c \
			raycaster/save.c

NAME    =   cub3d.out

HEAD	=	cub3d.h \
 			./raycaster/raycaster.h \
 			./map_validation/ft_validation.c \
 			./parser/ft_parser.h

LIBFT	=	./libft/libft.a

OBJS    =   $(SRCS:.c=.o)

GCC     =   gcc -Wall -Wextra -g -Werror

RM      =   rm -f

C       =   -c

O       =   -o


.PHONY:		all clean fclean re

.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)
all:		$(NAME)

$(NAME):    $(OBJS)
			make -C ./libft
			$(GCC) $(OBJS) ./libft/libft.a libmlx.dylib -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C ./libft
$(OBJS):	$(HEAD)
fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft

re:         fclean all