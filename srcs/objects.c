/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:47:43 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/15 23:36:33 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*create_obj(t_data *data, t_obj **obj)
{
	int	check;

	check = 0;
	while ((*obj))
	{
		if ((*obj)->pos.x == data->ray.mapx && (*obj)->pos.y ==
				data->ray.mapy)
			check = 1;
		obj = &((*obj)->next);
	}
	if (!check)
	{
		if (!((*obj) = malloc(sizeof(t_obj))))
			return (NULL);
		(*obj)->pos.x = data->ray.mapx;
		(*obj)->pos.y = data->ray.mapy;
		(*obj)->ray = data->ray;
		(*obj)->next = NULL;
	}
	return (obj);
}

void	free_obj(t_obj *obj)
{
	t_obj	*tmp;

	 while(obj)
    {
        tmp = obj->next;
        free(obj);
        obj = tmp;
    }
	 obj = NULL;
}


void	print_objects(t_data *data, int column, int i)
{
	t_img	rend;

	rend = data->sprite;
	if (data->map[data->][data->] == '2')
	{
		data->img.buffer[column + (i * (data->img.size / sizeof(int)))] = 0xFFFFFF;
	}
    /*dark(rend.buffer[20];(int)(((data->obj->ray.walldist * data->obj->ray.diry + data->obj->pos.y
    - (int)(data->obj->ray.walldist * data->obj->ray.diry + data->obj->pos.y)) * 750) +
(int)((int)((i - data->obj->ray.truestart) * (750 / (double)data->obj->ray.heightline)) *
    (rend.size / sizeof(int))))], data->obj->ray.walldist);*/
}
