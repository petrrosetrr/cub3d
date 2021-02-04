//
// Created by Jimmie Alease on 1/23/21.
//
#include "../cub3d.h"
#include "raycaster.h"

void DDA(int X0, int Y0, int X1, int Y1)
{
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	float Xinc = dx / (float) steps;
	float Yinc = dy / (float) steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++)
	{
		putpixel (X,Y,RED);  // put pixel at (X,Y)
		X += Xinc;           // increment in x at each step
		Y += Yinc;           // increment in y at each step
		delay(100);          // for visualization of line-
		// generation step by step
	}
}

void	draw_walls (t_vars *vars)
{
	double h, v, i;
	int x, y;
	int wh;
	double a;

	i = (double)FOV / -2;
	x = 0;
	while(i < (double)FOV*0.5)
	{
		a = vars->player.angle + i * DR;
		a = (a < -2 * PI) ? += 2 * PI: a;
		a = (a >  2 * PI) ? -= 2 * PI: a;
		h = get_horizontal_intersection(vars, a);
		v = get_vertical_intersection(vars, a);
		wh = (int)(floor((double) vars->p_struct.res[0] / ((((h < v) ? h : v)) * cos(i * M_PI / 180))));
		if (wh > vars->p_struct.res[1])
			wh = vars->p_struct.res[1];
		y = (int)(vars->p_struct.res[1] - wh) / 2;
		draw_line(vars, x, y, x, y + wh - 1, (h < v) ? 0xf5f5f5 : 0xfaebd7);
//			draw_texture(&vars->so_tex, vars, x + k, y, wh, (h < v) ? 'h' : 'v');
//			draw_texture(vars, x + k, y, wh);
		}
		x++;
		i += (double)FOV / (double)vars->p_struct.res[1];
	}
}
void	draw_texture(t_texture *texture, t_vars *vars, int x0, int y0, int wh, char wall)
{
	int k, ty, i, j;
	static int	wh_prev;
	static char	prev_wall;
	static int	tx;
	static int	tx_flag;

	if (wh_prev == 0 || prev_wall == 0 || prev_wall != wall || tx >= texture->img_width)
	{
		tx = 0;
		tx_flag = 0;
	}
	k = (int)(wh / (double)vars->no_tex.img_height);
	ty = 0;
	j = y0;
	while (ty < texture->img_height)
	{
		i = 0;
		while(i <= k && j < y0 + wh)
		{
//			my_mlx_pixel_get(texture, tx, ty)
			my_mlx_pixel_put(&vars->img, x0, j++, my_mlx_pixel_get(texture, tx, ty));
			i++;
		}
		ty++;
	}
	wh_prev = wh;
	prev_wall = wall;
	tx_flag++;
	if (tx_flag == k)
	{
		tx++;
		tx_flag = 0;
	}
}


void	draw_texture(t_vars *vars, int x, int y0, int wh)
{
	int k;
	int i;
	static int tx;

	i = 0;
	k = (int)((double)wh / (double)vars->so_tex.img_height);
	while(i < wh)
	{
		if (tx / k >= vars->so_tex.img_width)
			tx = 0;
		my_mlx_pixel_put(&vars->img, x, y0 + i, my_mlx_pixel_get(&vars->so_tex, tx / k, i / k));
		i++;
	}
	tx++;
}


void	draw_texture (t_vars *vars, s_w_intersection *intersection, int x, int y)
{
	int i;
	double k;
	i = 0;
	k = ((double)wh / (double)vars->so_tex.img_height);
	while(i < wh)
	{
		my_mlx_pixel_put(&vars->img, x, y + i, my_mlx_pixel_get(&vars->so_tex, floor(i / k), floor(vars->so_tex.line_length * intersection->wall_pos)));
		i++;
	}


}

