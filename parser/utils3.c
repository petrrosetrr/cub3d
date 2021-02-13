/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 03:41:26 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:27:02 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_parser.h"

void		set_values(t_struct *ms, char **rgb_arr, int spf)
{
	long int *arr;

	arr = (spf == 0) ? ms->floor : ms->ceiling;
	arr[0] = ft_atoi(rgb_arr[0]);
	arr[1] = ft_atoi(rgb_arr[1]);
	arr[2] = ft_atoi(rgb_arr[2]);
}

int			get_color(t_struct *ms, char *line, char *sp, int spf)
{
	char		**arr;
	char		**rgb_arr;
	static int	flag[2];

	if (flag[spf] != 0)
		return (0);
	if ((arr = ft_split(line, ' ')) != NULL && ft_strncmp(arr[0], sp, 1)
	== 0 && ft_strlen(arr[0]) == 1)
	{
		flag[spf] = 1;
		if ((n_of_lines(arr) == 2) && (rgb_arr = ft_split(arr[1], ','))
		!= NULL && n_of_lines(rgb_arr) == 3)
		{
			if (is_only_digits(rgb_arr[0]) &&
			is_only_digits(rgb_arr[1]) && is_only_digits(rgb_arr[2]))
			{
				set_values(ms, rgb_arr, spf);
				return (free_array(arr, 1) && free_array(rgb_arr, 1));
			}
			free_array(rgb_arr, 0);
		}
	}
	return (free_array(arr, 0));
}

int			get_fc_colors(t_struct *map_struct, char *line)
{
	if (line != NULL && ft_strnstr(line, "F ", ft_strlen(line)) != 0)
	{
		return (get_color(map_struct, line, "F ", 0));
	}
	else if (line != NULL && ft_strnstr(line, "C ", ft_strlen(line)) != 0)
	{
		return (get_color(map_struct, line, "C ", 1));
	}
	else
		return (0);
}
