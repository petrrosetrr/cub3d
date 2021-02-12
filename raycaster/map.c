/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:47:09 by jalease           #+#    #+#             */
/*   Updated: 2021/02/11 22:38:58 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

double				get_wall_dist(t_vars *vars, double angle)
{
	double h;
	double v;

	h = get_horizontal_intersection(vars, angle).distance;
	v = get_vertical_intersection(vars, angle).distance;
	return (h < v) ? h : v;
}

void				draw_ray(t_vars *vars, double angle)
{
	t_line line;
	double rl;

	rl = get_wall_dist(vars, angle) * vars->pixel_size;
	line.x0 = vars->player.x * vars->pixel_size;
	line.y0 = vars->player.y * vars->pixel_size;
	line.x1 = line.x0 + (rl * cos(angle));
	line.y1 = line.y0 + (rl * sin(angle));
	line.color = 0xff6a6a;
	draw_line(vars, line);
}

void				draw_rays(t_vars *vars)
{
	int		ps;
	double	k;

	ps = vars->pixel_size;
	my_mlx_pixel_put(&(vars->img), vars->player.x * ps,
	vars->player.y * ps, 0xeec900);
	k = -33;
	while (k < 33)
	{
		draw_ray(vars, vars->player.angle - (k += 0.05) * DR);
	}
}

void				fill_map_box(t_vars *vars, int x, int y, int color)
{
	int yy;
	int xx;
	int ps;

	ps = vars->pixel_size;
	yy = (y - vars->p_struct.map_start) * ps;
	while (yy < (y - vars->p_struct.map_start) * ps + ps)
	{
		xx = x * ps;
		while (xx < x * ps + ps)
		{
			my_mlx_pixel_put(&vars->img, xx, yy, color);
			xx++;
		}
		yy++;
	}
}

void				draw_map(t_vars *vars)
{
	int x;
	int y;

	y = vars->p_struct.map_start;
	while (vars->p_struct.map[y] != NULL)
	{
		x = 0;
		while (vars->p_struct.map[y][x] != '\0')
		{
			if (vars->p_struct.map[y][x] == '1')
				fill_map_box(vars, x, y, 0xe0ffff);
			if (vars->p_struct.map[y][x] == '0' ||
			ft_strchr("NSWE", vars->p_struct.map[y][x]) != NULL)
				fill_map_box(vars, x, y, 0x8ee5ee);
			if (vars->p_struct.map[y][x] == '2')
				fill_map_box(vars, x, y, 0x1e90ff);
			x++;
		}
		y++;
	}
	draw_rays(vars);
}
