/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 05:32:14 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:01:09 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_validation.h"

int		is_map_valid3(char **map, t_ms *f)
{
	while (map[f->i][f->k] != '\0')
	{
		if (f->i == 0 || map[f->i + 1] == NULL)
		{
			if (map[f->i][f->k] != '1' && map[f->i][f->k] != ' ')
				return (0);
		}
		else if (map[f->i][f->k] == '0' || ft_strchr(f->str, map[f->i][f->k])
		!= NULL || map[f->i][f->k] == '2')
		{
			if (check_zero(f->k, map[f->i - 1], map[f->i], map[f->i + 1]) == 0)
				return (0);
			if (ft_strchr(f->str, map[f->i][f->k]) != NULL)
			{
				if (f->flag == 0)
					f->flag++;
				else
					return (0);
			}
		}
		f->k++;
	}
	return (1);
}

int		is_map_valid2(char **map, t_ms *f)
{
	while (map[f->i] != NULL)
	{
		f->k = 0;
		if (map[f->i + 1] == NULL && map[f->i][0] == '\0')
			return (0);
		if (!is_map_valid3(map, f))
			return (0);
		f->i++;
	}
	return (1);
}

void	init_struct(t_ms *f)
{
	f->str = "NSEW";
	f->flag = 0;
	f->i = 0;
}

int		is_map_valid(char **map)
{
	t_ms f;

	init_struct(&f);
	if (!is_map_valid2(map, &f))
		return (0);
	if (f.flag == 0)
		return (0);
	return (1);
}
