/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:47:43 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 04:33:28 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_list(t_obj **obj)
{
	t_sac tmp;
	t_obj *head;

	head = *obj;
	while (*obj && (*obj)->next)
	{
		if ((*obj)->sac.ray.walldist < (*obj)->next->sac.ray.walldist)
		{
			tmp = (*obj)->sac;
			(*obj)->sac = (*obj)->next->sac;
			(*obj)->next->sac = tmp;
			obj = &head;
		}
		else
			obj = &(*obj)->next;
	}
}

void	init_idobj(t_data *data, t_obj *obj)
{
	data->idobj.spritex = obj->sac.ray.mapx - data->perso.pos.x + 0.5;
	data->idobj.spritey = obj->sac.ray.mapy - data->perso.pos.y + 0.5;
	data->idobj.invdet = 1.0 / (data->perso.planx * data->perso.dir.y -
			data->perso.dir.x * data->perso.plany);
	data->idobj.transformx = data->idobj.invdet * (data->perso.dir.y *
			data->idobj.spritex - data->perso.dir.x * data->idobj.spritey);
	data->idobj.transformy = data->idobj.invdet * (-data->perso.plany *
			data->idobj.spritex + data->perso.planx * data->idobj.spritey);
	data->idobj.spritescreenx = (int)((data->parse.width / 2) *
			(1 + data->idobj.transformx / data->idobj.transformy));
	data->idobj.spriteheight = ft_abs((int)(data->parse.height /
				data->idobj.transformy));
	data->idobj.drawstarty = -data->idobj.spriteheight / 2 +
		data->parse.height / 2;
	if (data->idobj.drawstarty < 0)
		data->idobj.drawstarty = 0;
	data->idobj.drawendy = data->idobj.spriteheight / 2 +
		data->parse.height / 2;
	if (data->idobj.drawendy >= data->parse.height)
		data->idobj.drawendy = data->parse.height - 1;
	data->idobj.spritewidth = ft_abs((int)(data->parse.height /
				(data->idobj.transformy)));
	init_idobj2(data);
}

void	print_obj(t_data *data, t_obj *obj)
{
	int	stripe;
	int	y;

	sort_list(&obj);
	while (obj)
	{
		init_idobj(data, obj);
		stripe = data->idobj.drawstartx - 1;
		while (++stripe < data->idobj.drawendx)
		{
			data->idobj.texx = (int)(256 * (stripe -
			(-data->idobj.spritewidth / 2 + data->idobj.spritescreenx))
			* obj->sac.sprite.width / data->idobj.spritewidth) / 256;
			if (data->idobj.transformy > 0 && stripe > 0 && stripe <
		data->parse.width && data->idobj.transformy < data->zbuffer[stripe])
			{
				y = data->idobj.drawstarty - 1;
				while (++y < data->idobj.drawendy)
					norme_obj(data, obj, y, stripe);
			}
		}
		obj = obj->next;
	}
}

void	*create_obj(t_data *data, t_obj **obj, int column, char c)
{
	while (*obj)
	{
		if ((int)((*obj)->sac.ray.mapx) == (int)(data->ray.mapx) &&
				(int)(data->ray.mapy) == (int)((*obj)->sac.ray.mapy))
			return (obj);
		obj = &((*obj)->next);
	}
	if (!(*obj = malloc(sizeof(t_obj))))
		return (NULL);
	if (c == '2')
		(*obj)->sac.sprite = data->sprite;
	if (c == '4')
		(*obj)->sac.sprite = data->sprite2;
	if (c == '5')
		(*obj)->sac.sprite = data->sprite3;
	if (c == '6')
		(*obj)->sac.sprite = data->sprite4;
	(*obj)->sac.ray = data->ray;
	(*obj)->sac.column = column;
	(*obj)->next = NULL;
	return (obj);
}

void	free_obj(t_obj *obj)
{
	t_obj	*tmp;

	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
	obj = NULL;
}
