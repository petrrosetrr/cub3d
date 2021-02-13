/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 06:16:16 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:19:02 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <limits.h>
# include <float.h>

typedef struct	s_struct
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		**map;
	long int	res[2];
	long int	floor[3];
	long int	ceiling[3];
	int			map_start;
	int			map_length;
	int			map_height;
}				t_struct;

t_struct		ft_parser(char *file_name);
int				map_validation(t_struct *map_struct);
void			raycaster(t_struct *p_struct, int screenshot);
#endif
