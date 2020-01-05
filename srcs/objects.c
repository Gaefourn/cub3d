/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:47:43 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/17 06:52:27 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*create_obj(t_data *data, t_obj **obj)
{
	data->check = 0;
	while ((*obj))
	{
		if ((*obj)->ray.mapx == data->ray.mapx && (*obj)->ray.mapy ==
				data->ray.mapy)
		{
			data->check = 1;
			return (obj);
		}
		obj = &((*obj)->next);
	}
	if (!data->check)
	{
		if (!((*obj) = malloc(sizeof(t_obj))))
			return (NULL);
		(*obj)->test = 1;
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


/*void	print_objects(t_data *data, int column, int i)
{
	t_img	rend;

	rend = data->sprite;
	if (data->map[data->][data->] == '2')
	{
		data->img.buffer[column + (i * (data->img.size / sizeof(int)))] = 0xFFFFFF;
	}
    dark(rend.buffer[20];(int)(((data->obj->ray.walldist * data->obj->ray.diry + data->obj->pos.y
    - (int)(data->obj->ray.walldist * data->obj->ray.diry + data->obj->pos.y)) * 750) +
(int)((int)((i - data->obj->ray.truestart) * (750 / (double)data->obj->ray.heightline)) *
    (rend.size / sizeof(int)))), data->obj->ray.walldist);
}*/
