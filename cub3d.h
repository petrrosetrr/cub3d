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

typedef struct	s_struct
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		**map;
	long int	res[2];
	long int    floor[3];
	long int	ceiling[3];
	int			map_start;
}				t_struct;
t_struct		ft_parser(char *file_name);
int				is_map_valid(t_struct *map_struct);
#endif
