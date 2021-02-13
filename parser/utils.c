/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 03:32:26 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 03:37:50 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_parser.h"

void		struct_init(t_struct *map_struct)
{
	size_t i;

	i = 0;
	while (i < 2)
		map_struct->res[i++] = -1;
	i = 0;
	while (i < 3)
	{
		map_struct->floor[i] = -1;
		map_struct->ceiling[i++] = -1;
	}
	map_struct->map_start = -1;
	map_struct->no = NULL;
	map_struct->we = NULL;
	map_struct->ea = NULL;
	map_struct->so = NULL;
	map_struct->s = NULL;
	map_struct->map = NULL;
}

int			is_f_valid(char *file_name)
{
	int i;
	int fd;

	i = ft_strlen(file_name);
	if (i < 5 || file_name[i - 1] != 'b' || file_name[i - 2] != 'u' ||
		file_name[i - 3] != 'c' || file_name[i - 4] != '.')
		return (0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	else
		close(fd);
	return (1);
}

int			file_to_array(char *file_name, t_struct *map_struct)
{
	int		fd;
	int		i;
	char	c;
	char	*line;

	i = 1;
	fd = open(file_name, O_RDONLY);
	while (read(fd, &c, 1))
		i = (c == '\n') ? i + 1 : i;
	map_struct->map = ft_calloc(i + 1, sizeof(char*));
	i = 0;
	close(fd);
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		map_struct->map[i++] = line;
	map_struct->map[i++] = line;
	map_struct->map[i] = NULL;
	close(fd);
	return (1);
}

int			is_only_digits(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int			get_first_line(char **map)
{
	int i;
	int k;

	i = 0;
	while (map[i] != NULL)
	{
		k = 0;
		while (map[i][k] != '\0')
		{
			if (!(map[i][k] == '1' || map[i][k] == ' '))
				break ;
			else
				k++;
		}
		if (map[i][k] == '\0' && ft_strchr(map[i], '1') != NULL)
			return (i);
		i++;
	}
	return (-1);
}
