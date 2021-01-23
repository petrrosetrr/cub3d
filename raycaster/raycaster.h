#ifndef RAYCASTER_H
# define RAYCASTER_H
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define SPEED 0.2
# define PI 3.1415926535
typedef struct  s_image {
	void        *img_ptr;
	char        *addr;
	int         bpp;
	int         line_length;
	int         endian;
}               t_image;

typedef struct	s_player
{
	double			x;
	double			y;
	int			flag_x;
	int			flag_y;
	double		angle;
}				t_player;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_image		img;
	t_player	player;
	t_struct	p_struct;
	int 		pixel_size;
}               t_vars;
#endif