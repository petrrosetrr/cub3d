/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:58 by jalease           #+#    #+#             */
/*   Updated: 2021/02/12 00:27:59 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

t_ff				ff(int x, int wh, double angle)
{
	t_ff f;

	f.x = x;
	f.wh = wh;
	f.angle = angle;
	return (f);
}

void				draw_walls(t_vars *vars)
{
	t_f_norm4	f;

	f.ray_step = (double)FOV / (double)vars->p_struct.res[0];
	f.i = (double)FOV / -2;
	f.x = 0;
	while (f.i < (double)FOV * 0.5)
	{
		f.a = vars->player.angle + f.i * DR;
		f.a = (f.a < -2 * PI) ? f.a + 2 * PI : f.a;
		f.a = (f.a > 2 * PI) ? f.a - 2 * PI : f.a;
		f.h = get_horizontal_intersection(vars, f.a);
		f.v = get_vertical_intersection(vars, f.a);
		f.wh = (int)(floor((double)vars->p_struct.res[1] /
		((((f.h.distance < f.v.distance)
		? f.h.distance : f.v.distance)) * cos(f.i * M_PI / 180))));
		draw_texture(vars, ((f.h.distance < f.v.distance)
		? &f.h : &f.v), ff(f.x, f.wh, f.a));
		draw_sprite(vars, f.h, f.v, f.x);
		f.x++;
		f.i += f.ray_step;
	}
}

int					redraw(t_vars *vars)
{
	vars->img.img_ptr = mlx_new_image(vars->mlx, vars->p_struct.res[0],
	vars->p_struct.res[1]);
	vars->img.addr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
	&vars->img.line_length, &vars->img.endian);
	move_player(vars, 0, 0);
	fill_fc(vars);
	draw_walls(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	return (1);
}

void				create_window(t_vars *vars)
{
	int x;
	int y;

	mlx_get_screen_size(vars->mlx, &x, &y);
	vars->p_struct.res[0] = (vars->p_struct.res[0] > x) ? x :
	vars->p_struct.res[0];
	vars->p_struct.res[1] = (vars->p_struct.res[1] > y) ? y :
	vars->p_struct.res[1];
	vars->win = mlx_new_window(vars->mlx, vars->p_struct.res[0],
	vars->p_struct.res[1], "cub3d");
	vars->pixel_size = ((vars->p_struct.res[0] / vars->p_struct.map_length) <
	(vars->p_struct.res[1] / vars->p_struct.map_height)) ? vars->p_struct.res[0]
	/ vars->p_struct.map_length : vars->p_struct.res[1] / vars->p_struct.
	map_height;
	vars->pixel_size = (vars->pixel_size * 0.4) > 5 ? vars->pixel_size *
	0.4 : 5;
}

void				raycaster(t_struct *p_struct)
{
	t_vars vars;

	vars.p_struct = *p_struct;
	vars.mlx = mlx_init();
	create_window(&vars);
	set_player(&vars);
	load_textures(&vars);
	mlx_hook(vars.win, 02, 0, pressed_hook, &vars);
	mlx_hook(vars.win, 03, 0, released_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop_hook(vars.mlx, redraw, &vars);
	mlx_loop(vars.mlx);
}
