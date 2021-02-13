/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:58:59 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:24:27 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

void			draw_line(t_vars *vars, t_line line)
{
	int			i;
	int			steps;
	double		x_inc;
	double		y_inc;

	steps = abs((int)(line.x1 - line.x0)) > abs((int)(line.y1 - line.y0))
	? abs((int)(line.x1 - line.x0)) : abs((int)(line.y1 - line.y0));
	x_inc = (line.x1 - line.x0) / (double)steps;
	y_inc = (line.y1 - line.y0) / (double)steps;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(&vars->img,
		floor(line.x0), floor(line.y0), line.color);
		line.x0 += x_inc;
		line.y0 += y_inc;
		i++;
	}
}

int				create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void			fill_fc(t_vars *vars)
{
	int x;
	int y;

	y = 0;
	while (y < vars->p_struct.res[1])
	{
		x = 0;
		while (x < vars->p_struct.res[0] && y < (vars->p_struct.res[1] / 2))
			my_mlx_pixel_put(&vars->img, x++, y, create_rgb(vars->p_struct.
			ceiling[0], vars->p_struct.ceiling[1], vars->p_struct.ceiling[2]));
		while (x < vars->p_struct.res[0] && y >= (vars->p_struct.res[1] / 2))
			my_mlx_pixel_put(&vars->img, x++, y, create_rgb(vars->p_struct.
			floor[0], vars->p_struct.floor[1], vars->p_struct.floor[2]));
		y++;
	}
}

void			set_ps(t_vars *vars)
{
	vars->pixel_size = ((vars->p_struct.res[0] / vars->p_struct.map_length) <
	(vars->p_struct.res[1] / vars->p_struct.map_height)) ?
	vars->p_struct.res[0] / vars->p_struct.map_length : vars->p_struct.res[1] /
	vars->p_struct.map_height;
	vars->pixel_size = (vars->pixel_size * 0.4) > 5 ?
	vars->pixel_size * 0.4 : 5;
}
