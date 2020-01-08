/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/08 04:57:00 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 800
# define HEIGHT 600
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
# define RUN 257
# define SCREENSHOT 105
# define ABS(Value) (Value < 0) ? -Value : Value

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

typedef	struct	s_sac
{
	int				column;
	t_img			sprite;
	t_ray			ray;
}				t_sac;

typedef struct	s_obj
{
	t_sac			sac;
	struct s_obj	*next;
}				t_obj;

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
	double		ZBuffer[WIDTH];
}				t_data;

void			*crt_img(t_data *data);
void			crt_column(t_data *data, int column);
void			raycasting(t_data *data, int x);
void			raycast_value(t_data *data, int x);
void			wall_dist(t_data *data);
void			init_ray(t_data *data, int x);
void			ft_init(t_data *data);
void			*ft_init_map(t_data *data);
void			ft_fill_map(t_data *data);
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
long            dark(int color, double walldist);
void			screenshot(t_data *data);
void			print_obj(t_data *data, t_obj *obj);

#endif
