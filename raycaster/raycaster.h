/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:00:41 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:25:26 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define SPEED 0.1
# define E_KEY 124
# define Q_KEY 123
# define PI 3.1415926535
# define DR 0.0174533
# define ANGLE_SPEED 0.05
# define FOV 60

typedef	struct			s_line
{
	double				x0;
	double				y0;
	double				x1;
	double				y1;
	unsigned int		color;
}						t_line;

typedef	struct			s_sprite
{
	double				hit[2];
	double				pos[2];
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_wall
{
	double				distance;
	double				wall_pos;
	char				flag;
	t_sprite			*sprite;
}						t_wall;

typedef struct			s_texture
{
	void				*img;
	int					img_width;
	int					img_height;
	int					bpp;
	int					line_length;
	int					endian;
	char				*addr;
}						t_texture;

typedef struct			s_image {
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_image;

typedef struct			s_player
{
	double				x;
	double				y;
	int					flag_x;
	int					flag_y;
	double				angle;
	int					flag_angle;
}						t_player;

typedef struct			s_vars {
	void				*mlx;
	void				*win;
	t_image				img;
	t_player			player;
	t_struct			p_struct;
	int					pixel_size;
	t_texture			no_tex;
	t_texture			so_tex;
	t_texture			we_tex;
	t_texture			ea_tex;
	t_texture			s_tex;
	int					screenshot;
}						t_vars;

typedef struct			s_f_norm
{
	double				dx;
	double				dy;
	char				**map;
	t_wall				intersection;
	int					flag;
}						t_f_norm;

typedef struct			s_f_norm2
{
	t_sprite			*sprite;
	int					i;
	int					y;
	int					wh;
	double				k;
	int					offset;
	double				distance;
	double				center_angle;
	double				ray_angle;
	double				sprite_pos;
}						t_f_norm2;

typedef struct			s_f_norm3
{
	int					y;
	int					offset;
	double				k[4];
	int					x;
	int					wh;
	double				angle;
	t_wall				*intersection;
}						t_f_norm3;

typedef struct			s_f_norm4
{
	t_wall				h;
	t_wall				v;
	double				i;
	double				ray_step;
	int					x;
	int					wh;
	double				a;
}						t_f_norm4;

typedef struct			s_ff
{
	int					x;
	int					wh;
	double				angle;
}						t_ff;

void					image_to_bmp(t_vars *vars);
void					my_mlx_pixel_put(
						t_image *image, int x, int y, int color);
int						my_mlx_pixel_get(t_texture *texture, int x, int y);
int						exit_hook(int keycode, t_vars *vars);
int						pressed_hook(int keycode, t_vars *vars);
int						released_hook(int keycode, t_vars *vars);

void					draw_line(t_vars *vars, t_line line);
int						create_rgb(int r, int g, int b);
void					fill_fc(t_vars *vars);

void					move_player(t_vars *vars, double dx, double dy);
void					set_player(t_vars *vars);

void					add_sprite
						(t_wall *wall, t_vars *vars, double dx, double dy);
void					draw_sprite(t_vars *vars, t_wall h, t_wall v, int x);

t_wall					get_vertical_intersection(t_vars *vars, double angle);
t_wall					get_horizontal_intersection(t_vars *vars, double angle);

void					draw_texture(
						t_vars *vars, t_wall *intersection, t_ff ff);

void					load_textures(t_vars *vars);

void					draw_map(t_vars *vars);
void					set_ps(t_vars *vars);
#endif
