# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalease <jalease@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 19:16:11 by jalease           #+#    #+#              #
#    Updated: 2020/11/03 21:44:46 by jalease          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
			ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_tolower.c ft_toupper.c \
			ft_isprint.c ft_isascii.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
NAME    =   libft.a
OBJS    =   $(SRCS:.c=.o)
GCC     =   gcc -Wall -Wextra -Werror
RM      =   rm -f
C       =   -c
O       =   -o
.PHONY:		all clean fclean re
.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)
$(NAME):    $(OBJS) $(HEAD)
			ar ruc  $(NAME) $(OBJS)
all:		$(NAME)
clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)
re:         fclean all