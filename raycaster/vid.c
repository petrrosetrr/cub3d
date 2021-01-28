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

