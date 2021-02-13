/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:32:26 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 05:34:53 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_validation.h"

int	is_textures_valid(t_struct *map_struct)
{
	int fd[5];
	int i;

	fd[0] = open(map_struct->no, O_RDONLY);
	fd[1] = open(map_struct->so, O_RDONLY);
	fd[2] = open(map_struct->we, O_RDONLY);
	fd[3] = open(map_struct->ea, O_RDONLY);
	fd[4] = open(map_struct->s, O_RDONLY);
	i = 0;
	while (i < 5)
	{
		if (fd[i] > 0)
			close(fd[i]);
		else
			return (0);
		i++;
	}
	return (1);
}

int	is_colors_valid(t_struct *map_struct)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (!((map_struct->ceiling[i] >= 0 && map_struct->ceiling[i] <= 255)
		&& (map_struct->floor[i] >= 0 && map_struct->floor[i] <= 255)))
			return (0);
		i++;
	}
	return (1);
}

int	is_res_valid(t_struct *map_struct)
{
	if (map_struct->res[0] <= 0 || map_struct->res[1] <= 0)
		return (0);
	return (1);
}

int	map_validation(t_struct *map_struct)
{
	if (is_textures_valid(map_struct) == 0
	|| is_colors_valid(map_struct) == 0
	|| is_res_valid(map_struct) == 0
	|| is_map_valid(&(map_struct->map[map_struct->map_start])) == 0)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (1);
}
