/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/17 06:14:06 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int		exit_properly(t_bool error, char *error_msg)
{
	int	i;

	i = 0;
//	system("killall afplay");
	if (error == TRUE)
	{
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
		exit(1);
	}
	exit(0);
}

int		key(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == ESC)
		exit_properly(FALSE, NULL);
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
	else if (key == DOOR)
		data->event.door ^= 1;
	else if (key == RUN)
		data->event.run ^= 1;
	return (0);
}

void	put_image_to_window(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->ciel.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->sol.ptr, 0, HEIGHT / 2);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
}

int		ft_move(t_data *data)
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
		data->perso.speed = 0.118;
	if (data->event.run == 0 && data->perso.speed != 0.066)
		data->perso.speed = 0.086;
	crt_img(data);
	put_image_to_window(data);
//	free_obj(data->obj);
	//data->obj = NULL;
	return (0);
}

int		main(void)
{
	t_data data;

	ft_init(&data);
	crt_window(&data);
	load_background(&data);
	load_textures(&data);
//	system("afplay sounds/bgm.mp3 &");
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
