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
	long int			res[2];
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	long int    floor[3];
	long int	ceiling[3];
	char		**map;
	int			map_size;
}				t_struct;
void *ft_parser(char *file_name);
#endif
