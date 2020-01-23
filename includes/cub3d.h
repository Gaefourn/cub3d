/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/23 21:53:36 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define KEYUP 3
# define KEYDOWN 2
# define ESC 53
# define QUIT 17
# define LEFT 0
# define RIGHT 2
# define FORWARD 13
# define BACKWARD 1
# define L_ARROW 123
# define R_ARROW 124
# define ACTION 14
# define RUN 257
# define SCREENSHOT 105

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <signal.h>
# include <fcntl.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef	struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef	struct	s_img
{
	void		*ptr;
	int			*buffer;
	int			bpp;
	int			size;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef	struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef	struct	s_perso
{
	t_pos		pos;
	t_pos		dir;
	double		planx;
	double		plany;
	double		speed;
	double		rot;
}				t_perso;

typedef	struct	s_event
{
	t_bool		forward;
	t_bool		backward;
	t_bool		left;
	t_bool		right;
	t_bool		l_arrow;
	t_bool		r_arrow;
	t_bool		door;
	t_bool		run;
	t_bool		screenshot;
}				t_event;

typedef	struct	s_ray
{
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltax;
	double		deltay;
	double		stepx;
	double		stepy;
	double		hit;
	double		side;
	double		walldist;
	int			start;
	int			end;
	int			truestart;
	int			trueend;
	double		dirx;
	double		diry;
	double		camera;
	int			heightline;
}				t_ray;

typedef struct	s_parse
{
	t_bool		check_res;
	t_bool		check_no;
	t_bool		check_so;
	t_bool		check_we;
	t_bool		check_ea;
	t_bool		check_sprite;
	t_bool		check_floor;
	t_bool		check_sky;
	int			width;
	int			height;
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;
	char		*sprite_tex;
	char		*sky_tex;
	char		*floor_tex;
	long		sky_col;
	long		floor_col;
}				t_parse;

typedef	struct	s_sac
{
	int			column;
	t_img		sprite;
	t_ray		ray;
}				t_sac;

typedef struct	s_obj
{
	t_sac			sac;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_idobj
{
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawstartx;
	int			drawendy;
	int			spritewidth;
	int			drawspritex;
	int			drawendx;
	int			texx;
	int			d;
	int			texy;
	int			color;
}				t_idobj;

typedef	struct	s_data
{
	t_perso		perso;
	t_img		img;
	t_mlx		mlx;
	t_event		event;
	t_ray		ray;
	t_img		ciel;
	t_img		sol;
	t_img		ntext;
	t_img		stext;
	t_img		etext;
	t_img		wtext;
	t_img		tmp_ciel;
	t_img		tmp_sol;
	t_img		tmp_ntext;
	t_img		tmp_stext;
	t_img		tmp_etext;
	t_img		tmp_wtext;
	t_img		sprite;
	t_img		sprite2;
	t_img		sprite3;
	t_img		sprite4;
	t_img		tmp_sprite2;
	t_img		tmp_sprite;
	t_img		tmp_sprite3;
	t_img		tmp_sprite4;
	t_obj		*obj;
	pid_t		music;
	int			check;
	char		**map;
	char		**map2;
	t_parse		parse;
	int			size_line;
	int			num_line;
	int			actu_line;
	double		*zbuffer;
	t_idobj		idobj;
}				t_data;

void			*crt_img(t_data *data);
void			crt_column(t_data *data, int column);
void			raycasting(t_data *data, int x);
void			raycast_value(t_data *data, int x);
void			wall_dist(t_data *data);
void			init_ray(t_data *data, int x);
void			ft_init(t_data *data);
void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			turn_left(t_data *data);
void			turn_right(t_data *data);
t_img			resize_image(t_data *data, t_img *src, int width, int height);
void			load_textures(t_data *data);
void			load_background(t_data *data);
void			crt_window(t_data *data);
void			*create_obj(t_data *data, t_obj **obj, int column, char c);
void			free_obj(t_obj *obj);
void			print_objects(t_data *data, int column, int i);
long			dark(int color, double walldist);
void			screenshot(t_data *data);
void			print_obj(t_data *data, t_obj *obj);
int				parse(char *path, t_parse *parse, t_data *data);
int				ft_atoi(const char *nptr);
void			init_parse(t_parse *parse);
void			parse_sky(char *str, t_parse *parse, t_bool *check);
long			create_hex(char *str);
void			read_map(t_data *data, char *buffer);
void			set_num_line(t_data *data, char *path);
int				check_line(char *buffer);
void			check_char(t_data *data);
void			norme_create_hex(char *str, int *r, int *g, int *b);
int				norme_main_parse(char *buffer, t_parse *parse);
void			norme_parse_sky(char *str, t_bool *check);
void			norme_main_parse2(char *buffer, t_parse *parse, t_data *data);
void			parse_res(char *str, t_parse *parse, t_bool *check);
void			parse_tex(char *str, char **tex, t_bool *check);
void			parse_floor(char *str, t_parse *parse, t_bool *check);
void			parse_sky(char *str, t_parse *parse, t_bool *check);
void			norme_parse_floor(char *str, t_bool *check);
void			init_idobj2(t_data *data);
void			norme_obj(t_data *data, t_obj *obj, int y, int stripe);
double			ft_abs(double nb);
int				parse_arg(char *str);
int				ft_strlen(char *str);
int				check_folder(char *str);
void			check_map_line(char *str, t_data *data);
void			first_and_last(t_data *data, char *str);

#endif
