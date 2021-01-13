#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct	s_struct
{
	int			res[2];
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			floor[3];
	int			ceiling[3];
	char		**map;
}				t_struct;
#endif
