//
// Created by Jimmie Alease on 1/23/21.
//
#include "../cub3d.h"
#include "raycaster.h"

void			my_draw_line(t_vars *vars, int X0, int Y0, int X1, int Y1)
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

void			move_player(t_vars *vars)
{
	double	dx, dy;
	char	**map;

	dx = SPEED * cos(vars->player.angle);
	dy = SPEED * sin(vars->player.angle);
}




