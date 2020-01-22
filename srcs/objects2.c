/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:39:57 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 02:56:54 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_idobj2(t_data *data)
{
	data->idobj.drawstartx = -data->idobj.spritewidth / 2 +
		data->idobj.spritescreenx;
	if (data->idobj.drawstartx < 0)
		data->idobj.drawstartx = 0;
	data->idobj.drawendx = data->idobj.spritewidth / 2 +
		data->idobj.spritescreenx;
	if (data->idobj.drawendx >= data->parse.width)
		data->idobj.drawendx = data->parse.width - 1;
}

void	norme_obj(t_data *data, t_obj *obj, int y, int stripe)
{
	data->idobj.d = y * 256 - data->parse.height * 128 +
		data->idobj.spriteheight * 128;
	data->idobj.texy = ((data->idobj.d *
				obj->sac.sprite.height) / data->idobj.spriteheight) / 256;
	if (obj->sac.sprite.width *
			data->idobj.texy + data->idobj.texx > 0)
		data->idobj.color =
			dark(obj->sac.sprite.buffer[(obj->sac.sprite.width *
						data->idobj.texy + data->idobj.texx)],
					obj->sac.ray.walldist);
	if ((data->idobj.color & 0x00FFFFFF) != 0)
	{
		data->img.buffer[stripe + (y *
				(data->img.size / sizeof(int)))] =
			data->idobj.color;
	}
}
