/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:32:26 by jalease           #+#    #+#             */
/*   Updated: 2021/01/15 20:32:29 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_textures_valid(t_struct *map_struct)
{
	int fd[5];
	int i;

	fd[0] = open(map_struct->no, O_RDONLY);
	fd[1] = open(map_struct->so, O_RDONLY);
	fd[2] = open(map_struct->we, O_RDONLY);
	fd[3] = open(map_struct->ea, O_RDONLY);
	fd[4] = open(map_struct->s, O_RDONLY);
	i = 0;
	while(i < 5)
	{
		if (fd[i] > 0)
			close(fd[i]);
		else
			return (0);
		i++;
	}
	return (1);
}

int is_colors_valid(t_struct *map_struct)
{
	int i;

	i = 0;
	while(i < 3)
	{
		if (!((map_struct->ceiling[i] >= 0 && map_struct->ceiling[i] <= 255)
		&& (map_struct->floor[i] >= 0 && map_struct->floor[i] <= 255)))
			return (0);
		i++;
	}
	return (1);
}

int is_res_valid(t_struct *map_struct)
{
	//TODO:Дописать проверку на разрешение экрана компьютера
	if (map_struct->res[0] <= 0 || map_struct->res[1] <= 0)
		return (0);
	if (map_struct->res[0] > 1920 || map_struct->res[1] > 1080)
	{
		map_struct->res[0] = 1920;
		map_struct->res[1] = 1080;
	}
	return (1);
}

int is_map_valid(t_struct *map_struct)
{

}

