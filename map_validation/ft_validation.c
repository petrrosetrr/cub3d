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

int check_zero(int i, char *prev, char *this, char *next)
{
	int length[3];
	char *str;

	str = "012NSWE";
	length[0] = ft_strlen(prev) - 1;
	length[1] = ft_strlen(this) - 1;
	length[2] = ft_strlen(next) - 1;

	if (i == 0 || length[1] == i)
		return (0);
	if (ft_strchr(str, this[i - 1]) != NULL && ft_strchr(str, this[i + 1]) != NULL)
	{
		if (length[0] > i && length[2] > i)
		{
			if (i == length[1] - 1)
			{
				if (prev[i + 1] != '1' || this[i + 1] != '1' || next[i + 1] != '1')
					return (0);
			}
			else if (i == 1)
			{
				if (prev[i - 1] != '1' || this[i - 1] != '1' || next[i - 1] != '1')
					return (0);
			}
			if (!(ft_strchr(str, prev[i - 1]) && ft_strchr(str, prev[i]) && ft_strchr(str, prev[i + 1])))
				return (0);
			if (!(ft_strchr(str, next[i - 1]) && ft_strchr(str, next[i]) && ft_strchr(str, next[i + 1])))
				return (0);
		}
		else
			return (0);
		return (1);
	}
	return (0);
}

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
			//TODO: исправть когда подвезут текстуры
			return (1);
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
int is_map_valid(char **map)
{
	int i, k;
	int flag;
	char *str;

	str = "NSEW";
	flag = 0;
	i = 0;
	while (map[i] != NULL)
	{
		k = 0;
		while (map[i][k + 1] != '\0')
		{
			if (i == 0 || map[i + 1] == NULL)
			{
				if (map[i][k] != '1' && map[i][k] != ' ')
					return (0);
			}
			else
			{
				if (map[i][k] == '0' || ft_strchr(str, map[i][k]) != NULL)
				{
					if (check_zero(k, map[i - 1], map[i], map[i + 1]) == 0)
						return (0);
					if (ft_strchr(str, map[i][k]) != NULL)
					{
						if (flag == 0)
							flag++;
						else
							return (0);
					}
				}

			}
			k++;
		}
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

int map_validation(t_struct *map_struct)
{
	//TODO: валидация игрока
	if (is_textures_valid(map_struct) == 0
	|| is_colors_valid(map_struct) == 0
	|| is_res_valid(map_struct) == 0
	|| is_map_valid(&(map_struct->map[map_struct->map_start])) == 0)
	{
		write(2, "Map is invalid\n", ft_strlen("Map is invalid\n"));
		exit(1);
	}
	return (1);
}