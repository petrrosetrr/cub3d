/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:31:59 by jalease           #+#    #+#             */
/*   Updated: 2021/02/11 20:01:10 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

int				get_dir(double angle, char flag)
{
	if (flag == 'v')
	{
		if ((angle < 90 * DR && angle > -90 * DR) ||
			(angle <= -270 * DR && angle >= -360 * DR) ||
			(angle >= 270 * DR && angle <= 360 * DR))
			return (1);
		else if ((angle > 90 * DR && angle < 270 * DR) ||
				(angle < -90 * DR && angle > -270 * DR))
			return (-1);
		return (0);
	}
	else
	{
		if ((angle > 0 && angle < 180 * DR) ||
		(angle < -180 * DR && angle > -360 * DR))
			return (1);
		else if ((angle < 0 && angle > -180 * DR) ||
		(angle > 180 * DR && angle < 360 * DR))
			return (-1);
		return (0);
	}
}

int				init_f(t_vars *vars, t_f_norm *f, double angle, char flag)
{
	f->intersection.sprite = NULL;
	f->map = &vars->p_struct.map[vars->p_struct.map_start];
	f->flag = get_dir(angle, flag);
	f->dx = DBL_MAX;
	f->dy = DBL_MAX;
	return (1);
}

t_wall			get_horizontal_intersection(t_vars *vars, double angle)
{
	t_f_norm f;

	if (init_f(vars, &f, angle, 'h') == 1 && f.flag != 0)
	{
		f.dy = (f.flag > 0) ? ceil(vars->player.y) - vars->
		player.y + 0.0001 : floor(vars->player.y) - vars->player.y - 0.0001;
		f.dx = (fabs(angle) == 90 * DR || fabs(angle) == 270 * DR) ? 0 : f.dy
		/ tan(angle);
		while (vars->p_struct.map_height > (int)(vars->player.y + f.dy) &&
		vars->player.y + f.dy >= 0 && (int)(vars->player.x + f.dx) >= 0 && (int)
		(vars->player.x + f.dx) < (int)ft_strlen(f.map[(int)(vars->player.y +
		f.dy)]) && f.map[(int)(vars->player.y + f.dy)][(int)(vars->player.x +
		f.dx)] != '1')
		{
			(f.map[(int)(vars->player.y + f.dy)][(int)(vars->player.x + f.dx)]
			== '2') ? add_sprite(&f.intersection, vars, f.dx, f.dy) : 0;
			f.dy += (f.flag > 0) ? 1 : -1;
			f.dx += (f.flag > 0) ? 1.0 / tan(angle) : -1.0 / tan(angle);
		}
	}
	f.intersection.distance = (sqrt(pow(f.dx, 2) + pow(f.dy, 2)));
	f.intersection.wall_pos = ((f.dx) + (vars->player.x)) - floor((f.dx)
	+ (vars->player.x));
	f.intersection.flag = 'h';
	return (f.intersection);
}

t_wall			get_vertical_intersection(t_vars *vars, double angle)
{
	t_f_norm f;

	if (init_f(vars, &f, angle, 'v') == 1 && f.flag != 0)
	{
		f.dx = (f.flag > 0) ? ceil(vars->player.x) - vars->player.x + 0.0001 :
		floor(vars->player.x) - vars->player.x - 0.0001;
		f.dy = f.dx * tan(angle);
		while (vars->p_struct.map_height > (int)(vars->player.y + f.dy) &&
		vars->player.y + f.dy >= 0 && (int)(vars->player.x + f.dx) >= 0 &&
		(int)(vars->player.x + f.dx) < (int)ft_strlen(f.map[(int)(vars->
		player.y + f.dy)]) && f.map[(int)(vars->player.y + f.dy)]
		[(int)(vars->player.x + f.dx)] != '1')
		{
			if (f.map[(int)(vars->player.y + f.dy)]
			[(int)(vars->player.x + f.dx)] == '2')
				add_sprite(&f.intersection, vars, f.dx, f.dy);
			f.dx += (f.flag > 0) ? 1 : -1;
			f.dy += (f.flag > 0) ? tan(angle) : -tan(angle);
		}
	}
	f.intersection.wall_pos = ((f.dy) + (vars->player.y))
	- floor((f.dy) + (vars->player.y));
	f.intersection.distance = (sqrt(pow(f.dx, 2) + pow(f.dy, 2)));
	f.intersection.flag = 'v';
	return (f.intersection);
}
