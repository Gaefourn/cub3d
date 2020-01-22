/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 17:46:11 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 01:58:27 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			load_textures(t_data *data)
{
	data->ntext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.no_tex,
						&(data->ntext.width), &(data->ntext.height));
	data->stext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.so_tex,
						&(data->stext.width), &(data->stext.height));
	data->etext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.ea_tex,
						&(data->etext.width), &(data->etext.height));
	data->wtext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.we_tex,
						&(data->wtext.width), &(data->wtext.height));
	data->tmp_ntext = resize_image(data, &data->ntext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	data->ntext = data->tmp_ntext;
	data->tmp_stext = resize_image(data, &data->stext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	data->stext = data->tmp_stext;
	data->tmp_etext = resize_image(data, &data->etext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	data->etext = data->tmp_etext;
	data->tmp_wtext = resize_image(data, &data->wtext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
	data->wtext = data->tmp_wtext;
}

static void		load_background2(t_data *data)
{
	data->sprite.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.sprite_tex,
			&(data->sprite.width), &(data->sprite.height));
	data->tmp_sprite = resize_image(data, &data->sprite, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->sprite.ptr);
	data->sprite = data->tmp_sprite;
	data->sprite2.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/morty.xpm",
			&(data->sprite2.width), &(data->sprite2.height));
	data->tmp_sprite2 = resize_image(data, &data->sprite2, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->sprite2.ptr);
	data->sprite2 = data->tmp_sprite2;
	data->sprite3.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/squanch.xpm",
			&(data->sprite3.width), &(data->sprite3.height));
	data->tmp_sprite3 = resize_image(data, &data->sprite3, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->sprite3.ptr);
	data->sprite3 = data->tmp_sprite3;
	data->sprite4.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/meeseeks.xpm",
			&(data->sprite4.width), &(data->sprite4.height));
	data->tmp_sprite4 = resize_image(data, &data->sprite4, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->sprite4.ptr);
	data->sprite4 = data->tmp_sprite4;
}

void			load_background(t_data *data)
{
	if (data->parse.sky_tex)
	{
		data->ciel.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			data->parse.sky_tex,
						&(data->ciel.width), &(data->ciel.height));
		data->tmp_ciel = resize_image(data, &data->ciel, data->parse.width,
			data->parse.height / 2);
		mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
		data->ciel = data->tmp_ciel;
	}
	if (data->parse.floor_tex)
	{
		data->sol.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		data->parse.floor_tex, &(data->sol.width), &(data->sol.height));
		data->tmp_sol = resize_image(data, &data->sol, data->parse.width,
			data->parse.height / 2);
		mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
		data->sol = data->tmp_sol;
	}
	load_background2(data);
}

void			crt_window(t_data *data)
{
	data->mlx.ptr = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.ptr, data->parse.width,
			data->parse.height, "Cub3d");
	data->img.ptr = mlx_new_image(data->mlx.ptr, data->parse.width,
			data->parse.height);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
										&data->img.size, &data->img.endian);
}
