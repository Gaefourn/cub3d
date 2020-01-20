/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:49 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 05:39:19 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, int x)
{
	data->ray.camera = (2 * x / (double)data->parse.width) - 1;
	data->ray.dirx = data->perso.dir.x + data->perso.planx * data->ray.camera;
	data->ray.diry = data->perso.dir.y + data->perso.plany * data->ray.camera;
	data->ray.mapx = (int)data->perso.pos.x;
	data->ray.mapy = (int)data->perso.pos.y;
	data->ray.sidedistx = 0;
	data->ray.sidedisty = 0;
	data->ray.deltax = sqrt(1 + ((data->ray.diry * data->ray.diry) /
				(data->ray.dirx * data->ray.dirx)));
	data->ray.deltay = sqrt(1 + ((data->ray.dirx * data->ray.dirx) /
				(data->ray.diry * data->ray.diry)));
	data->ray.stepx = 0;
	data->ray.stepy = 0;
	data->ray.hit = 0;
	data->ray.side = 0;
	data->ray.walldist = 0;
}

void	ft_init(t_data *data)
{
	data->perso.rot = 4 * M_PI / 180;
	data->event.forward = 0;
	data->event.backward = 0;
	data->perso.speed = 0.88;
	data->event.left = 0;
	data->event.right = 0;
	data->event.l_arrow = 0;
	data->event.r_arrow = 0;
	data->event.run = 0;
	data->event.screenshot = 0;
	data->size_line = 0;
	data->num_line = 0;
	data->actu_line = 0;
	if (!(data->zbuffer = malloc(sizeof(double) * data->parse.width)))
	{
		write(2, "Malloc error.\n", 14);
		exit(0);
	}
	data->obj = NULL;
}

void	init_parse(t_parse *parse)
{
	parse->check_res = FALSE;
	parse->check_no = FALSE;
	parse->check_so = FALSE;
	parse->check_we = FALSE;
	parse->check_ea = FALSE;
	parse->check_floor = FALSE;
	parse->check_sky = FALSE;
	parse->check_sprite = FALSE;
	parse->width = 0;
	parse->height = 0;
}
