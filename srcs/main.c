/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 03:33:02 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

static int		exit_properly(t_data *data)
{
	write(1, "Cub3d s'est correctement fermé.\n", 33);
	free_images(data);
	free_path(data);
	exit(0);
}

static int		key(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(data);
	else if (key == FORWARD)
		data->event.forward ^= 1;
	else if (key == BACKWARD)
		data->event.backward ^= 1;
	else if (key == RIGHT)
		data->event.right ^= 1;
	else if (key == LEFT)
		data->event.left ^= 1;
	else if (key == R_ARROW)
		data->event.r_arrow ^= 1;
	else if (key == L_ARROW)
		data->event.l_arrow ^= 1;
	else if (key == RUN)
		data->event.run ^= 1;
	else if (key == SCREENSHOT)
		data->event.screenshot ^= 1;
	else if (key == ACTION)
		data->event.door ^= 1;
	return (0);
}

static void		ft_norme(t_data *data)
{
	if (data->event.forward == 1)
		move_forward(data);
	if (data->event.backward == 1)
		move_backward(data);
	if (data->event.right == 1)
		move_right(data);
	if (data->event.left == 1)
		move_left(data);
	if (data->event.r_arrow == 1)
		turn_right(data);
	if (data->event.l_arrow == 1)
		turn_left(data);
	if (data->event.door == 1 && data->map[(int)(data->perso.pos.x +
			(data->perso.dir.x * data->perso.speed))][(int)(data->perso.pos.y +
						(data->perso.dir.y * data->perso.speed))] == '3')
		data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
					data->perso.speed))][(int)(data->perso.pos.y +
								(data->perso.dir.y * data->perso.speed))] = '0';
	if (data->event.run == 1)
		data->perso.speed = 0.1200;
	if (data->event.run != 1)
		data->perso.speed = 0.0800;
	if (data->event.screenshot == 1)
		screenshot(data);
}

static int		ft_move(t_data *data)
{
	ft_norme(data);
	crt_img(data);
	if (data->obj)
	{
		print_obj(data, data->obj);
		free_obj(data->obj);
		data->obj = NULL;
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	return (0);
}

int				main(int ac, char **av)
{
	t_data data;

	if (ac < 2 || ac > 3)
	{
		write(2, "Error,\nWrong numbers of argument.\n", 34);
		return (0);
	}
	if (parse_arg(av[1], &data) == -1)
	{
		write(2, "Error,\nMap file is invalid.\n", 28);
		return (0);
	}
	parse(av[1], &data.parse, &data);
	ft_init(&data);
	crt_window(&data);
	load_background(&data);
	load_textures(&data);
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
