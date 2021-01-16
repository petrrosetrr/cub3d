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
		printf("\n\n->>> main <<<<---\n");
		printf("res:      %ld %ld\n", map->res[0], map->res[1]);
        printf("north:    %s\n", map->no);
        printf("south:    %s\n", map->so);
        printf("west:     %s\n", map->we);
        printf("east:     %s\n", map->ea);
        printf("sprite:   %s\n\n", map->s);
        printf("map size: %d\n", map->map_size);
        printf("floor: %ld %ld %ld\n", map->floor[0],map->floor[1],map->floor[2]);
        printf("ceiling: %ld %ld %ld\n\n", map->ceiling[0],map->floor[1],map->floor[2]);
        while(map->map[i] != NULL) {
            printf(">|%s|<\n", map->map[i]);
            free(map->map[i++]);
        }
        free(map->map[i]);
        free(map->map);
        free(map->no);
        free(map->so);
        free(map->we);
        free(map->ea);
        free(map->s);
        free(map);
//        while(1);
	}
	else
	{
	}
	return (0);
}
