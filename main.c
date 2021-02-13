/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:13:43 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:15:01 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_struct map;

	if (argc == 2 || argc == 3)
	{
		map = ft_parser(argv[1]);
		if (map_validation(&map) == 1)
		{
			if (argc == 2)
				raycaster(&map, 0);
			else if (argc == 3 && ft_strncmp("--save", argv[2],
			ft_strlen("--save")) == 0)
				raycaster(&map, 1);
			else
			{
				ft_putstr_fd("Error\n", 2);
				exit(1);
			}
		}
	}
	return (0);
}
