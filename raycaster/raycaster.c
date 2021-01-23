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
	return (1);
}
void			draw_line(t_vars *vars, int X0, int Y0, int X1, int Y1)
{
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	double Xinc = dx / (double) steps;
	double Yinc = dy / (double) steps;

	// Put pixel for each step
	double X = X0;
	double Y = Y0;
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
void			draw_player(t_vars *vars)
{
	int ps;
	ps = vars->pixel_size;
	//TODO: хранить позицию игрока на карте и позицию игрока на экране?
	printf("player x y %.2f %.2f\n", (vars->player.y) * ps, (vars->player.x) * ps);
	for(int y = floor(vars->player.y * ps); y < floor(vars->player.y * ps) + ps; y++)
	{
		for (int x = (int)floor(vars->player.x * ps); x < (int)floor(vars->player.x * ps) + ps; x++)
		{
			my_mlx_pixel_put(&(vars->img), x, y, 0xeec900);
		}
	}
}
void			move_player(t_vars *vars)
{
	if (vars->player.flag_x > 0)
		vars->player.x+= SPEED;
	if (vars->player.flag_y > 0)
		vars->player.y+= SPEED;
	if (vars->player.flag_x < 0)
		vars->player.x-= SPEED;
	if (vars->player.flag_y < 0)
		vars->player.y-= SPEED;
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
}
void 			set_player (t_vars     *vars)
{
	char *str;
	int i, k;

	vars->player.flag_x = 0;
	vars->player.flag_y = 0;
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
	draw_line(&vars, 0, 0, 100, 150);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop_hook(vars.mlx, redraw, &vars);
	mlx_loop(vars.mlx);
}