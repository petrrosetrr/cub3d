/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:13:43 by jalease           #+#    #+#             */
/*   Updated: 2021/01/11 15:13:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
    int i = 0;
	if (argc == 2 || argc == 3)
	{
		t_struct *map = (t_struct*)ft_parser(argv[1]);
//		free(map);
        printf("%s\n", map->no);
        printf("what\n");
        printf("%s\n", map->so);
        printf("what\n");
        printf("%s\n", map->we);
        printf("%s\n", map->ea);
        printf("%s\n", map->s);
        printf("floor: %ld %ld %ld\n", map->floor[0],map->floor[1],map->floor[2]);
        printf("ceiling: %ld %ld %ld\n", map->ceiling[0],map->floor[1],map->floor[2]);
        while(map->map[i] != NULL)
            printf(">|%s|<\n", map->map[i++]);
	}
	else
	{
		//error
	}
	return (0);
}
