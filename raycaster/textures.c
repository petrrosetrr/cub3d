/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:42:46 by jalease           #+#    #+#             */
/*   Updated: 2021/02/12 00:28:49 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

void
	load_textures(t_vars *vars)
{
	if ((vars->no_tex.img = mlx_xpm_file_to_image(vars->mlx, vars->p_struct.no,
	&vars->no_tex.img_width, &vars->no_tex.img_height)) == NULL || (vars->
	so_tex.img = mlx_xpm_file_to_image(vars->mlx, vars->p_struct.so, &vars->
	so_tex.img_width, &vars->so_tex.img_height)) == NULL || (vars->we_tex.img =
	mlx_xpm_file_to_image(vars->mlx, vars->p_struct.we, &vars->we_tex.
	img_width, &vars->we_tex.img_height)) == NULL || (vars->ea_tex.img =
	mlx_xpm_file_to_image(vars->mlx, vars->p_struct.ea, &vars->ea_tex.
	img_width, &vars->ea_tex.img_height)) == NULL || (vars->s_tex.img =
	mlx_xpm_file_to_image(vars->mlx, vars->p_struct.s, &vars->s_tex.
	img_width, &vars->s_tex.img_height)) == NULL)
	{
		write(2, "error", ft_strlen("error"));
		exit(1);
	}
	vars->no_tex.addr = mlx_get_data_addr(vars->no_tex.img, &vars->no_tex.bpp,
	&vars->no_tex.line_length, &vars->no_tex.endian);
	vars->so_tex.addr = mlx_get_data_addr(vars->so_tex.img, &vars->so_tex.bpp,
	&vars->so_tex.line_length, &vars->so_tex.endian);
	vars->we_tex.addr = mlx_get_data_addr(vars->we_tex.img, &vars->we_tex.bpp,
	&vars->we_tex.line_length, &vars->we_tex.endian);
	vars->ea_tex.addr = mlx_get_data_addr(vars->ea_tex.img, &vars->ea_tex.bpp,
	&vars->ea_tex.line_length, &vars->ea_tex.endian);
	vars->s_tex.addr = mlx_get_data_addr(vars->s_tex.img, &vars->s_tex.bpp,
	&vars->s_tex.line_length, &vars->s_tex.endian);
}

void
	put_texture(t_vars *vars, t_f_norm3 *f, int i, char flag)
{
	t_texture *t;

	t = NULL;
	t = (flag == 'n') ? &vars->no_tex : t;
	t = (flag == 's') ? &vars->so_tex : t;
	t = (flag == 'w') ? &vars->we_tex : t;
	t = (flag == 'e') ? &vars->ea_tex : t;
	my_mlx_pixel_put(&vars->img, f->x, f->y + i,my_mlx_pixel_get(
	t, floor(t->img_width * f->intersection->wall_pos), floor(
	(double)(i + f->offset) / f->k[0])));
}

void
	draw_texture2(t_vars *vars, t_f_norm3 *f)
{
	int i;

	i = -1;
	while (++i < f->wh)
	{
		if (f->intersection->flag == 'h')
		{
			if ((f->angle >= 0 && f->angle <= 180 * DR) ||
			(f->angle <= -180 * DR && f->angle >= -360 * DR))
				put_texture(vars, f, i, 'n');
			else if ((f->angle > 180 * DR && f->angle <= 360 * DR)
			|| (f->angle <= 0 * DR && f->angle > -180 * DR))
				put_texture(vars, f, i, 's');
		}
		else if (f->intersection->flag == 'v')
		{
			if ((f->angle >= 0 && f->angle <= 90 * DR) || (f->angle >= 270 * DR
			&& f->angle <= 360 * DR) || (f->angle < 0 && f->angle >= -90 * DR)
			|| (f->angle <= -270 * DR && f->angle >= -360 * DR))
				put_texture(vars, f, i, 'e');
			else if ((f->angle > 90 * DR && f->angle < 270 * DR) ||
			(f->angle < -90 * DR && f->angle > -270 * DR))
				put_texture(vars, f, i, 'w');
		}
	}
}

void
	draw_texture(t_vars *vars, t_wall *intersection, t_ff ff)
{
	t_f_norm3	f;

	f.k[0] = ((double)ff.wh / (double)vars->no_tex.img_height);
	f.k[1] = ((double)ff.wh / (double)vars->so_tex.img_height);
	f.k[2] = ((double)ff.wh / (double)vars->we_tex.img_height);
	f.k[3] = ((double)ff.wh / (double)vars->ea_tex.img_height);
	f.offset = 0;
	f.y = ((int)vars->p_struct.res[1] > ff.wh) ?
	(((int)vars->p_struct.res[1] - ff.wh) / 2) : 0;
	if (ff.wh > vars->p_struct.res[1])
	{
		f.offset = (ff.wh - (int)vars->p_struct.res[1]) / 2;
		ff.wh = (int)vars->p_struct.res[1];
	}
	f.wh = ff.wh;
	f.angle = ff.angle;
	f.x = ff.x;
	f.intersection = intersection;
	draw_texture2(vars, &f);
}
