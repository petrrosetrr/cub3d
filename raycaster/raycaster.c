#include "../cub3d.h"
#include "raycaster.h"

void            my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char    *dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int*)dst = color;
}
int             exit_hook(int keycode, t_vars *vars)
{
	(void) keycode;
	(void) vars;
	printf("EXIT HOOK\n\n");
	exit(0);
}
int				pressed_hook(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->player.flag_y = -1;
	if (keycode == S_KEY)
		vars->player.flag_y = 1;
	if (keycode == A_KEY)
		vars->player.flag_x = -1;
	if (keycode == D_KEY)
		vars->player.flag_x = 1;
	if (keycode == ESC_KEY)
		exit_hook(keycode, vars);
	if(keycode == E_KEY)
		vars->player.flag_angle = 1;
	if(keycode == Q_KEY)
		vars->player.flag_angle = -1;
	return (1);
}
int				released_hook(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->player.flag_y = 0;
	if (keycode == S_KEY)
		vars->player.flag_y = 0;
	if (keycode == A_KEY)
		vars->player.flag_x = 0;
	if (keycode == D_KEY)
		vars->player.flag_x = 0;
	if(keycode == E_KEY)
		vars->player.flag_angle = 0;
	if(keycode == Q_KEY)
		vars->player.flag_angle = 0;
	return (1);
}

void			draw_map(t_vars *vars)
{
	int x, y, ps;

	ps = vars->pixel_size;
	y = vars->p_struct.map_start;
	while(vars->p_struct.map[y] != NULL)
	{
		x = 0;
		while(vars->p_struct.map[y][x] != '\0')
		{
			if (vars->p_struct.map[y][x] == '1')
				for(int yy = (y - vars->p_struct.map_start) * ps; yy < (y - vars->p_struct.map_start) * ps + ps; yy++)
				{
					for (int xx = x * ps; xx < x * ps + ps; xx++)
					{
						my_mlx_pixel_put(&vars->img, xx, yy, 0xe0ffff);
					}
				}
			if (vars->p_struct.map[y][x] == '0' || vars->p_struct.map[y][x] == '2' || vars->p_struct.map[y][x] == 'N')
				for(int yy = (y - vars->p_struct.map_start) * ps; yy < (y - vars->p_struct.map_start) * ps + ps; yy++)
				{
					for (int xx = x * ps; xx < x * ps + ps; xx++)
					{
						my_mlx_pixel_put(&vars->img, xx, yy, 0x8ee5ee);
					}
				}
			x++;
		}
		y++;
	}
}
//double			get_wall_dist(t_vars *vars, double angle)
//{
//	double dx1, dy1;
//	double dx2, dy2;
//	int flag[2];
//	char **map = &vars->p_struct.map[vars->p_struct.map_start];
//	if ((angle > 0 && angle < PI / 2.0) || (angle < -270. * DR && angle > - 2.0 * PI) )
//	{
//		// +x +y
//		dy1 = ceil(vars->player.y) - vars->player.y;
//		dx1 = dy1 / tan(angle) + 0.0001;
//		while (vars->p_struct.map_height > (int)(vars->player.y + dy1) &&
//		ft_strlen(map[(int)(vars->player.y + dy1)]) > (int)(dx1 + vars->player.x)
//		&& map[(int)(vars->player.y + dy1)][(int)(dx1 + vars->player.x)] != '1')
//		{
//			dy1++;
//			dx1 += 1/tan(angle);
//		}
//		dx2 = ceil(vars->player.x) - vars->player.x;
//		dy2 = tan(vars->player.angle) * dx2 + 0.0001;
//		while(vars->p_struct.map_height > (int)(vars->player.y + dy2) &&
//		ft_strlen(map[(int)(vars->player.y + dy2)]) > (int)(dx2 + vars->player.x) &&
//		map[(int)(vars->player.y + dy2)][(int)(dx2 + vars->player.x)] != '1')
//		{
//			dx2++;
//			dy2 += tan(vars->player.angle);
//		}
//		return ((sqrt(pow(dy1, 2) + pow(dx1, 2)) < sqrt(pow(dy2, 2) + pow(dx2, 2))) ?
//		sqrt(pow(dy1, 2) + pow(dx1, 2)) : sqrt(pow(dy2, 2)+ pow(dx2, 2)));
//	}
//	else if ((angle < PI && angle > PI / 2.0) || (angle < -PI && angle > -1.5 * PI) )
//	{
//		// -x +y
//		dy1 = ceil(vars->player.y) - vars->player.y;
//		dx1 = dy1 / tan(angle) - 0.0001;
//		while (vars->p_struct.map_height > (int)(vars->player.y + dy1) &&
//			   (int)(vars->player.x - dx1 + flag[0]) >= 0
//			   && map[(int)(vars->player.y + dy1)][(int)(vars->player.x + dx1 + flag[0])] != '1')
//		{
//			flag[0] = 0;
//			dy1++;
//			dx1 += 1/tan(angle);
//		}
//		dx2 = vars->player.x - ceil(vars->player.x);
//		dy2 = tan(vars->player.angle) * dx2 + 0.0001;
//		while(vars->p_struct.map_height > (int)(vars->player.y + dy2)&&
//				(int)(vars->player.x + dx2 + flag[1]) >= 0 &&
//			  map[(int)(vars->player.y + dy2)][(int)(vars->player.x + dx2) + flag[1]] != '1')
//		{
//			flag[1] = 0;
//			dx2--;
//			dy2 += -tan(vars->player.angle);
//		}
//		return ((sqrt(pow(dy1, 2) + pow(fabs(dx1), 2)) < sqrt(pow(dy2, 2) + pow(fabs(dx2), 2))) ?
//		sqrt(pow(dy1, 2) + pow(fabs(dx1), 2)) : sqrt(pow(dy2, 2)+ pow(fabs(dx2), 2)));
//	}
//	else
//		return (-1);
//}
double			get_horizontal_intersection(t_vars *vars, double angle, char **map)
{
	double dx, dy;

	dx = DBL_MAX;
	dy = DBL_MAX;
	if (angle == 90 * DR || angle == -270 * DR)
	{
		dy = ceil(vars->player.y) - vars->player.y + 0.0001;
		dx = 0;
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dy++;
		}
	}
	else if (angle == -90 * DR || angle == 270 * DR)
	{
		dy = floor(vars->player.y) - vars->player.y - 0.0001;
		dx = 0;
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dy--;
		}
	}
	else if (angle == 0 * DR || angle == 360 * DR || angle == 180 * DR || angle == -180 * DR || angle == -360 * DR)
	{
		dx = DBL_MAX;
		dy = DBL_MAX;
	}
	else if ((angle > 0 &&  angle < 180 * DR ) || (angle < -180 * DR && angle > -360 * DR))
	{
		dy = ceil(vars->player.y) - vars->player.y + 0.0001;
		dx = dy / tan(angle);
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
		&& (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
		&& map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dy++;
			dx+= 1.0 / tan(angle);
		}
	}
	else if ((angle < 0 &&  angle > -180 * DR ) || (angle > 180 * DR && angle < 360 * DR))
	{
		//TODO: 3 четверть
		dy = floor(vars->player.y) - vars->player.y - 0.0001;
		dx = dy / tan(angle);
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dy--;
			dx+=  -1.0 / tan(angle);
		}
	}
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}
double			get_vertical_intersection(t_vars *vars, double angle, char **map)
{
	double dx, dy;

	dx = DBL_MAX;
	dy = DBL_MAX;
	if (angle == 90 * DR || angle == -270 * DR || angle == -90 * DR || angle == 270 * DR)
	{
		dx = DBL_MAX;
		dy = DBL_MAX;
	}
	else if (angle == 0 * DR || angle == 360 * DR || angle == -360 * DR)
	{
		dx = ceil(vars->player.y) - vars->player.y + 0.0001;
		dy = 0;
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dx++;
		}
	}
	else if (angle == 180 * DR || angle == -180 * DR)
	{
		dx = floor(vars->player.y) - vars->player.y - 0.0001;
		dy = 0;
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dx--;
		}
	}
	else if ((angle < 90 * DR && angle > -90 * DR) || (angle < -270 * DR && angle > -360 * DR) || (angle > 270 * DR && angle < 360 * DR))
	{
		dx = ceil(vars->player.x) - vars->player.x + 0.0001;
		dy = dx * tan(angle);
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dx++;
			dy+= tan(angle);
		}
	}
	else if ((angle > 90 * DR && angle < 270 * DR) || (angle < -90 * DR && angle > -270 * DR))
	{
		//TODO: 3 четверть
		dx = floor(vars->player.x) - vars->player.x - 0.0001;
		dy = dx * tan(angle);
		while(vars->p_struct.map_height > (int)(vars->player.y + dy) && vars->player.y + dy >= 0
			  && (int)(vars->player.x + dx) >= 0 && (int)(vars->player.x + dx) < (int)ft_strlen(map[(int)(vars->player.y + dy)])
			  && map[(int)(vars->player.y + dy)][(int)(vars->player.x + dx)] != '1')
		{
			dx--;
			dy+= -tan(angle);
		}
	}
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}
double			get_wall_dist(t_vars *vars, double angle)
{
	double h, v;
	char **map;

	map = &vars->p_struct.map[vars->p_struct.map_start];
	h = get_horizontal_intersection(vars, angle, map);
	v = get_vertical_intersection(vars, angle, map);
	return (h < v) ? h : v;
}





void			my_draw_line(t_vars *vars, double angle)
{
	double rl = (get_wall_dist(vars, angle) != -1) ? get_wall_dist(vars, angle) * vars->pixel_size : 100;
	double x0 = vars->player.x * vars->pixel_size;
	double y0 = vars->player.y * vars->pixel_size;
	double x1 = x0 + (rl * cos(angle));
	double y1 = y0 + (rl * sin(angle));
	// calculate dx & dy
	double dx = x1 - x0;
	double dy = y1 - y0;

	// calculate steps required for generating pixels
	int steps = abs((int)dx) > abs((int)dy) ? abs((int)dx) : abs((int)dy);

	// calculate increment in x & y for each steps
	double Xinc = dx / (double) steps;
	double Yinc = dy / (double) steps;

	// Put pixel for each step
	double X = x0;
	double Y = y0;
	for (int i = 0; i <= steps; i++)
	{
//		putpixel (X,Y,RED);  // put pixel at (X,Y)
		my_mlx_pixel_put(&vars->img, floor(X), floor(Y), 0xff6a6a);
		X += Xinc;           // increment in x at each step
		Y += Yinc;           // increment in y at each step
//		delay(100);          // for visualization of line-
		// generation step by step
	}
}

void			draw_player(t_vars *vars)
{
	int ps;
	ps = vars->pixel_size;
	//TODO: хранить позицию игрока на карте и позицию игрока на экране?
	printf("player x y angle %.2f %.2f %.2f\n", (vars->player.y) * ps, (vars->player.x) * ps, vars->player.angle / DR);
				my_mlx_pixel_put(&(vars->img), vars->player.x * ps, vars->player.y * ps, 0xeec900);

//	for(int y = floor(vars->player.y * ps); y < floor(vars->player.y * ps) + ps; y++)
//	{
//		for (int x = (int)floor(vars->player.x * ps); x < (int)floor(vars->player.x * ps) + ps; x++)
//		{
//			my_mlx_pixel_put(&(vars->img), x, y, 0xeec900);
//		}
//	}
	int k;
	k = -33;
	for(int i = 0; i < 66; i++)
	{
		my_draw_line(vars, vars->player.angle - (k++)*DR);
	}
		my_draw_line(vars, vars->player.angle);

}
void			move_player(t_vars *vars)
{
	double	dx = 0, dy = 0;
	char	**map;

	map = &vars->p_struct.map[vars->p_struct.map_start];
	if (vars->player.flag_x > 0)
	{
		dy = SPEED * sin(90*DR + vars->player.angle);
		dx = SPEED * cos(90*DR + vars->player.angle);
	}
	if (vars->player.flag_y > 0)
	{
		dy = -SPEED * sin(vars->player.angle);
		dx = -SPEED * cos(vars->player.angle);
	}
	if (vars->player.flag_x < 0)
	{
		dy = -SPEED * sin(90*DR + vars->player.angle);
		dx = -SPEED * cos(90*DR + vars->player.angle);
	}
	if (vars->player.flag_y < 0)
	{
		dy = SPEED * sin(vars->player.angle);
		dx = SPEED * cos(vars->player.angle);
	}

	if (map[(int)(vars->player.y)][(int)(vars->player.x + dx)] != '1' &&
			map[(int)(vars->player.y)][(int)(vars->player.x + dx)] != '2')
	{
		vars->player.x += dx;

	}
	if (map[(int)(vars->player.y + dy)][(int)(vars->player.x)] != '1' &&
		map[(int)(vars->player.y + dy)][(int)(vars->player.x)] != '2')
	{
		vars->player.y += dy;

	}
	if (vars->player.flag_angle > 0)
		vars->player.angle += ANGLE_SPEED;
	if (vars->player.flag_angle < 0)
		vars->player.angle -= ANGLE_SPEED;
	if (vars->player.angle >= DR * 360)
		vars->player.angle -= DR * 360;
	if (vars->player.angle <= -360*DR)
		vars->player.angle += DR * 360;
}
int				redraw(t_vars *vars)
{
	vars->img.img_ptr = mlx_new_image(vars->mlx, vars->p_struct.res[0], vars->p_struct.res[1]);
	vars->img.addr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp, &vars->img.line_length, &vars->img.endian);
	move_player(vars);
	draw_map(vars);
	draw_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	//TODO: пофиксить утечки памяти
	return (1);
}
void 			create_window (t_vars *vars)
{
	int x;
	int y;

	mlx_get_screen_size(vars->mlx, &x, &y);
	vars->p_struct.res[0] = (vars->p_struct.res[0] > x) ? x : vars->p_struct.res[0];
	vars->p_struct.res[1] = (vars->p_struct.res[1] > y) ? x : vars->p_struct.res[1];
	vars->win = mlx_new_window(vars->mlx, vars->p_struct.res[0], vars->p_struct.res[1], "cub3d");
	vars->pixel_size = ((vars->p_struct.res[0] / vars->p_struct.map_length) < (vars->p_struct.res[1] / vars->p_struct.map_height)) ?
					   vars->p_struct.res[0] / vars->p_struct.map_length : vars->p_struct.res[1] / vars->p_struct.map_height;
	printf("screen x y %d %d res %d %d\n\n",x, y, vars->p_struct.res[0], vars->p_struct.res[1]);
}
void 			set_player (t_vars     *vars)
{
	char *str;
	int i, k;

	vars->player.flag_x = 0;
	vars->player.flag_y = 0;
	vars->player.flag_angle = 0;
	vars->player.angle = START_ANGLE*DR;
	i = vars->p_struct.map_start;
	str = "NSEW";
	while(vars->p_struct.map[i] != NULL)
	{
		k = 0;
		while(vars->p_struct.map[i][k] != '\0')
		{
			if (ft_strchr(str, vars->p_struct.map[i][k]) != NULL)
			{
				vars->player.x = k+ 0.5;
				vars->player.y = i - vars->p_struct.map_start + 0.5;
				printf("%f %f", vars->player.x, vars->player.y);
				return;
			}
			k++;
		}
		i++;
	}
}
void 			raycaster(t_struct *p_struct)
{
	t_vars      vars;

	vars.p_struct = *p_struct;
	vars.mlx = mlx_init();
	create_window(&vars);
	set_player(&vars);
	vars.img.img_ptr = mlx_new_image(vars.mlx, vars.p_struct.res[0], vars.p_struct.res[1]);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bpp, &vars.img.line_length, &vars.img.endian);
	mlx_hook(vars.win, 02, 0, pressed_hook, &vars);
	mlx_hook(vars.win, 03, 0, released_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop_hook(vars.mlx, redraw, &vars);
	mlx_loop(vars.mlx);
}
