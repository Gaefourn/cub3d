/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 17:34:29 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/19 23:49:45 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				*get_texture(t_data *data)
{
	if (data->map[data->ray.mapx][data->ray.mapy] == '1' ||
			data->map[data->ray.mapx][data->ray.mapy] == '3')
	{
		if (data->ray.side == 1)
		{
			if (data->ray.stepy == -1)
				return (data->ntext.buffer);
			if (data->ray.stepy == 1)
				return (data->stext.buffer);
		}
		if (data->ray.stepx == -1)
			return (data->etext.buffer);
	}
	return (data->wtext.buffer);
}

long			dark(int color, double walldist)
{
	unsigned char	*byte;
	double			calcul;

	byte = (unsigned char *)&color;
	calcul = ((walldist / 10.5) + 1);
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = 0;
	return ((long)color);
}

long			trans(int color, t_data *data, int i)
{
	unsigned char	*byte;
	double			calcul;
	double			calcul2;

	byte = (unsigned char *)&color;
	calcul = ((data->ray.walldist / 10.5) + 1);
	calcul2 = (i * ((data->ray.end - data->ray.start) / HEIGHT) +
			(data->ray.walldist)) * 16.5;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	if (*byte + calcul2 < 255 && i < 2 * data->ray.end - data->ray.start)
		*byte += calcul2;
	else
		*byte = 255;
	return ((long)color);
}

static void		crt_wall(t_data *data, int column, int i, int *rend)
{
	if (data->ray.side == 1)
		data->img.buffer[column + (i * (data->img.size / sizeof(int)))] =
			dark(rend[(int)(((data->ray.walldist * data->ray.dirx + data->perso.pos.x
								- (int)(data->ray.walldist * data->ray.dirx + data->perso.pos.x)) * 750) +
						(int)((int)((i - data->ray.truestart) * (750 / (double)data->ray.heightline)) *
							(data->ntext.size / sizeof(int))))], data->ray.walldist);
	else
		data->img.buffer[column + (i * (data->img.size / sizeof(int)))] =
			dark(rend[(int)(((data->ray.walldist * data->ray.diry + data->perso.pos.y
								- (int)(data->ray.walldist * data->ray.diry + data->perso.pos.y)) * 750) +
						(int)((int)((i - data->ray.truestart) * (750 / (double)data->ray.heightline)) *
							(data->ntext.size / sizeof(int))))], data->ray.walldist);
}

void			crt_column(t_data *data, int column)
{
	int		i;
	int		*texture;
	int		*rend;

	i = -1;
	texture = get_texture(data);
	while (++i < data->ray.start)
	{
		if (data->parse.sky_tex)
			data->img.buffer[column + (i * (data->img.size / 4))] = data->ciel.buffer[column + (i * (data->img.size / 4))];
		else
			data->img.buffer[column + (i * (data->img.size / 4))] =
				data->parse.sky_col;
	}
	i--;
	while (++i < data->ray.end)
	{
		rend = texture;
		crt_wall(data, column, i, rend);
	}
	i--;
	while (++i < HEIGHT)
	{
		if (data->parse.floor_tex)
			data->img.buffer[column + (i * (data->img.size / sizeof(int)))] = data->sol.buffer[column + ((i - (HEIGHT / 2)) * (data->img.size / 4))];
		else
			data->img.buffer[column + (i * (data->img.size / 4))] =
				data->parse.floor_col;
	}
}
