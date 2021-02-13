/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 02:08:38 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 05:26:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_parser.h"

int			set_resolution(char **arr, t_struct *map_struct)
{
	if (ft_strlen(arr[1]) < 8 && ft_strlen(arr[2]) < 8)
	{
		map_struct->res[0] = ft_atoi(arr[1]);
		map_struct->res[1] = ft_atoi(arr[2]);
	}
	else
	{
		map_struct->res[0] = 100000;
		map_struct->res[1] = 100000;
	}
	return (free_array(arr, 1));
}

int			get_resolution(t_struct *map_struct, char *line)
{
	char		**arr;
	static int	flag;

	if (line != NULL && ft_strnstr(line, "R ",
	ft_strlen(line)) != 0 && flag == 0)
	{
		arr = ft_split(line, ' ');
		if (arr != NULL && ft_strncmp(arr[0], "R", 1) == 0
		&& ft_strlen(arr[0]) == 1)
		{
			flag = 1;
			if (n_of_lines(arr) == 3)
			{
				if (is_only_digits(arr[1]) && is_only_digits(arr[2]))
				{
					return (set_resolution(arr, map_struct));
				}
			}
		}
		return (free_array(arr, 0));
	}
	return (0);
}

int			set_texture(char **line, char **arr, int index)
{
	static int	flag[5];

	if (flag[index] == 0)
	{
		flag[index] = 1;
		*line = ft_strdup(arr[1]);
		return (free_array(arr, 1));
	}
	else
		return (free_array(arr, 0));
}

int			get_textures(t_struct *map_struct, char *line)
{
	char		**arr;

	if (line != NULL && (arr = ft_split(line, ' '))
	!= NULL && n_of_lines(arr) == 2)
	{
		if (ft_strncmp(arr[0], "NO", 2) == 0 && ft_strlen(arr[0]) == 2)
			return (set_texture(&map_struct->no, arr, 0));
		else if (ft_strncmp(arr[0], "SO", 2) == 0 && ft_strlen(arr[0]) == 2)
			return (set_texture(&map_struct->so, arr, 1));
		else if (ft_strncmp(arr[0], "WE", 2) == 0 && ft_strlen(arr[0]) == 2)
			return (set_texture(&map_struct->we, arr, 2));
		else if (ft_strncmp(arr[0], "EA", 2) == 0 && ft_strlen(arr[0]) == 2)
			return (set_texture(&map_struct->ea, arr, 3));
		else if (ft_strncmp(arr[0], "S", 1) == 0 && ft_strlen(arr[0]) == 1)
			return (set_texture(&map_struct->s, arr, 4));
		return (free_array(arr, 0));
	}
	return (0);
}

t_struct	ft_parser(char *file_name)
{
	t_struct	map_struct;
	int			i;

	struct_init(&map_struct);
	if (!is_f_valid(file_name) || !file_to_array(file_name, &map_struct)
		|| (map_struct.map_start = get_map_start(map_struct.map)) < 8)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	i = 0;
	while (i < map_struct.map_start)
	{
		if (!(get_resolution(&map_struct, map_struct.map[i])
		|| get_fc_colors(&map_struct, map_struct.map[i])
		|| get_textures(&map_struct, map_struct.map[i])
		|| is_empty(map_struct.map[i])))
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		i++;
	}
	set_map_size(&map_struct);
	return (map_struct);
}
