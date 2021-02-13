/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 03:37:24 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 03:40:01 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_parser.h"

int			get_map_start(char **map)
{
	int		i;
	int		k;
	char	*s;
	int		start;

	s = " 012NSWE";
	start = get_first_line(map);
	i = start;
	while (map[i] != NULL)
	{
		k = 0;
		while (map[i][k] != '\0')
		{
			if (ft_strchr(s, map[i][k]) == NULL)
				return (-1);
			k++;
		}
		i++;
	}
	return (start);
}

int			n_of_lines(char **map)
{
	int i;

	i = 0;
	while (map != NULL && map[i] != NULL)
	{
		i++;
	}
	return (i);
}

int			free_array(char **array, int code)
{
	int i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i++]);
		}
		free(array[i]);
		free(array);
	}
	return (code);
}

void		set_map_size(t_struct *map_struct)
{
	int i;
	int max;
	int map_height;

	map_height = 0;
	max = 0;
	i = map_struct->map_start;
	while (map_struct->map[i])
	{
		max = ((int)ft_strlen(map_struct->map[i]) > max)
		? (int)ft_strlen(map_struct->map[i]) : max;
		i++;
		map_height++;
	}
	map_struct->map_height = map_height;
	map_struct->map_length = max;
}

int			is_empty(char *line)
{
	if (*line == '\0')
		return (1);
	else
		return (0);
}
