/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:20:11 by jalease           #+#    #+#             */
/*   Updated: 2021/02/11 22:29:05 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

void
	add_sprite(t_wall *wall, t_vars *vars, double dx, double dy)
{
	t_sprite *tmp;

	tmp = wall->sprite;
	wall->sprite = malloc(sizeof(t_sprite));
	wall->sprite->next = tmp;
	wall->sprite->pos[0] = floor(vars->player.x + dx) + 0.5 - vars->player.x;
	wall->sprite->pos[1] = floor(vars->player.y + dy) + 0.5 - vars->player.y;
	wall->sprite->hit[0] = dx;
	wall->sprite->hit[1] = dy;
}

void
	free_sprites(t_sprite *v, t_sprite *h, int flag)
{
	static t_sprite *vs;
	static t_sprite *hs;
	t_sprite		*tmp;

	if (flag == 1)
	{
		vs = v;
		hs = h;
	}
	else
	{
		while (vs != NULL)
		{
			tmp = vs->next;
			free(vs);
			vs = tmp;
		}
		while (hs != NULL)
		{
			tmp = hs->next;
			free(hs);
			hs = tmp;
		}
	}
}

t_sprite
	*get_sprite(t_wall *h, t_wall *v)
{
	t_sprite *sprite;

	if ((h->sprite != NULL && v->sprite != NULL &&
	(sqrt(pow(h->sprite->pos[0], 2) + pow(h->sprite->pos[1], 2)) >
	sqrt(pow(v->sprite->pos[0], 2) + pow(v->sprite->pos[1], 2))))
	|| v->sprite == NULL)
	{
		sprite = h->sprite;
		h->sprite = h->sprite->next;
	}
	else
	{
		sprite = v->sprite;
		v->sprite = v->sprite->next;
	}
	return (sprite);
}

void
	draw_sprite2(t_vars *vars, t_wall *h, t_wall *v, t_f_norm2 *f)
{
	f->sprite = get_sprite(h, v);
	f->distance = sqrt(pow(f->sprite->pos[0], 2) + pow(f->sprite->pos[1], 2));
	f->center_angle = atan(f->sprite->pos[1] / f->sprite->pos[0]);
	f->ray_angle = atan(f->sprite->hit[1] / f->sprite->hit[0]);
	f->sprite_pos = 1;
	if (fabs(f->center_angle) > 45 * DR)
	{
		f->center_angle = atan(f->sprite->pos[0] / f->sprite->pos[1]);
		f->ray_angle = atan(f->sprite->hit[0] / f->sprite->hit[1]);
		f->sprite_pos = -1;
	}
	f->sprite_pos *= fabs(sin(fabs(f->ray_angle - f->center_angle)) *
	f->distance);
	if (f->ray_angle < f->center_angle)
		f->sprite_pos *= -1;
	f->wh = (int)(floor((double)vars->p_struct.res[1] / f->distance));
	if (f->wh > vars->p_struct.res[1])
	{
		f->offset = (f->wh - (int)vars->p_struct.res[1]) / 2;
		f->wh = (int)vars->p_struct.res[1];
	}
	f->y = (vars->p_struct.res[1] - f->wh) / 2 + f->wh * 0.5;
	f->k = (f->wh * 0.5 + f->offset) / vars->s_tex.img_height;
}

void
	draw_sprite(t_vars *vars, t_wall h, t_wall v, int x)
{
	t_f_norm2 f;

	f.offset = 0;
	free_sprites(h.sprite, v.sprite, 1);
	while (h.sprite != NULL || v.sprite != NULL)
	{
		draw_sprite2(vars, &h, &v, &f);
		if (h.distance < f.distance || v.distance < f.distance)
			continue;
		f.i = 0;
		if (f.sprite_pos >= -0.5 && f.sprite_pos <= 0.5)
		{
			while (f.i < f.wh / 2)
			{
				if (my_mlx_pixel_get(&vars->s_tex, floor(vars->s_tex.img_width *
				(0.5 + f.sprite_pos)), floor((double)(f.i) / f.k)) != 0x0)
					my_mlx_pixel_put(&vars->img, x, f.y + f.i, my_mlx_pixel_get(
					&vars->s_tex, floor(vars->s_tex.img_width * (0.5 +
					f.sprite_pos)), floor((double)(f.i) / f.k)));
				f.i++;
			}
		}
		f.sprite = NULL;
	}
	free_sprites(h.sprite, v.sprite, 0);
}
