#ifndef RAYCASTER_H
# define RAYCASTER_H
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define SPEED 0.1
# define E_KEY 14
# define Q_KEY 12
# define PI 3.1415926535
# define DR 0.0174533
# define START_ANGLE 90
# define ANGLE_SPEED 0.05
# define FOV 60
# define RAY 1450

typedef struct	s_w_intersection
{
	double		intersection;
	double		wall_pos;
	char		flag;
}				s_w_intersection;

typedef struct	s_texture
{
	void 		*img;
	int			img_width;
	int 		img_height;
	int			bpp;
	int			line_length;
	int			endian;
	char		*addr;
}				t_texture;
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
	int			flag_angle;
}				t_player;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_image		img;
	t_player	player;
	t_struct	p_struct;
	int 		pixel_size;
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
}               t_vars;
#endif