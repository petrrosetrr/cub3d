/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:09:44 by jalease           #+#    #+#             */
/*   Updated: 2021/02/10 17:27:11 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

void				check_walls(t_vars *vars, double dx, double dy)
{
	char	**map;

	map = &vars->p_struct.map[vars->p_struct.map_start];
	if (map[(int)(vars->player.y)][(int)(vars->player.x + dx)] != '1' &&
		map[(int)(vars->player.y)][(int)(vars->player.x + dx)] != '2')
		vars->player.x += dx;
	if (map[(int)(vars->player.y + dy)][(int)(vars->player.x)] != '1' &&
		map[(int)(vars->player.y + dy)][(int)(vars->player.x)] != '2')
		vars->player.y += dy;
	if (vars->player.flag_angle > 0)
		vars->player.angle += ANGLE_SPEED;
	if (vars->player.flag_angle < 0)
		vars->player.angle -= ANGLE_SPEED;
	if (vars->player.angle >= DR * 360)
		vars->player.angle -= DR * 360;
	if (vars->player.angle <= -360 * DR)
		vars->player.angle += DR * 360;
}

void				move_player(t_vars *vars, double dx, double dy)
{
	if (vars->player.flag_x > 0)
	{
		dy += SPEED * sin(90 * DR + vars->player.angle);
		dx += SPEED * cos(90 * DR + vars->player.angle);
	}
	if (vars->player.flag_y > 0)
	{
		dy += -SPEED * sin(vars->player.angle);
		dx += -SPEED * cos(vars->player.angle);
	}
	if (vars->player.flag_x < 0)
	{
		dy += -SPEED * sin(90 * DR + vars->player.angle);
		dx += -SPEED * cos(90 * DR + vars->player.angle);
	}
	if (vars->player.flag_y < 0)
	{
		dy += SPEED * sin(vars->player.angle);
		dx += SPEED * cos(vars->player.angle);
	}
	check_walls(vars, dx, dy);
}

double				set_player_angle(char c)
{
	if (c == 'N')
		return (270 * DR);
	else if (c == 'S')
		return (90 * DR);
	else if (c == 'W')
		return (180 * DR);
	else if (c == 'E')
		return (0);
	return (0);
}

void				set_player(t_vars *vars)
{
	char	*str;
	int		i;
	int		k;

	vars->player.flag_x = 0;
	vars->player.flag_y = 0;
	vars->player.flag_angle = 0;
	i = vars->p_struct.map_start;
	str = "NSEW";
	while (vars->p_struct.map[i] != NULL)
	{
		k = 0;
		while (vars->p_struct.map[i][k] != '\0')
		{
			if (ft_strchr(str, vars->p_struct.map[i][k]) != NULL)
			{
				vars->player.x = k + 0.5;
				vars->player.y = i - vars->p_struct.map_start + 0.5;
				vars->player.angle = set_player_angle(vars->p_struct.map[i][k]);
				return ;
			}
			k++;
		}
		i++;
	}
}
