/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:26:15 by jalease           #+#    #+#             */
/*   Updated: 2021/02/12 19:26:35 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "raycaster.h"

int		get_pixel(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(int*)dst);
}

void	int_to_char(unsigned char *line, int d)
{
	int i;

	i = 0;
	while (i < 4)
	{
		line[i] = (unsigned char)(d >> 8 * i);
		i++;
	}
}

void	add_data(t_vars *vars, int fd)
{
	int i;
	int k;
	int a;

	i = vars->p_struct.res[1] - 1;
	while(i >= 0)
	{
		k = 0;
		while(k < vars->p_struct.res[0])
		{
			a = get_pixel(&vars->img, k, i);
			write(fd, &a, vars->img.bpp / 8);
			k++;
		}
		i--;
	}
}

void 	add_header(t_vars *vars, int fd, int f_size)
{
	unsigned char header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(&header[2], f_size);
	int_to_char(&header[10], 54);
	int_to_char(&header[14], 40);
	int_to_char(&header[18], vars->p_struct.res[0]);
	int_to_char(&header[22], vars->p_struct.res[1]);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(vars->img.bpp);
	write(fd, header, 54);
}

void	image_to_bmp(t_vars *vars)
{
	int fd;
	int f_size;

	f_size = 54 + (vars->img.line_length * vars->p_struct.res[1]);
	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0777)) < 0)
	{
		write(2, "error", ft_strlen("error"));
		exit(1);
	}
	add_header(vars, fd, f_size);
	add_data(vars, fd);
	close(fd);
	exit(0);
}
