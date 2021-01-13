/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:28:02 by jalease           #+#    #+#             */
/*   Updated: 2020/11/19 21:29:05 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# define BUFFER_SIZE 1000

size_t		ft_strlen(const char *s);
char		*ft_strndup(const char *s1, size_t n);
int			ft_strcut(char **tbuf, long int start);
long int	find_n(char *str);
int			ft_strrealloc(char **tbuf);
void		*ft_calloc(size_t count, size_t size);
int			ft_free(char **tbuf, int ret_value);
long int	ft_read(int fd, char **tbuf);
int			get_next_line_2(char **tbuf, long int rs, int fd, char **line);
int			get_next_line(int fd, char **line);
#endif
