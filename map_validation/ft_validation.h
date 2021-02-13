/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 05:32:52 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:13:40 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VALIDATION_H
# define FT_VALIDATION_H

typedef struct	s_ms
{
	int			i;
	int			k;
	int			flag;
	char		*str;
}				t_ms;

typedef struct	s_cz
{
	int			length[3];
	char		*str;
	char		*prev;
	char		*this;
	char		*next;
}				t_cz;
int				check_zero(int i, char *prev, char *this, char *next);\
int				is_map_valid(char **map);
#endif
