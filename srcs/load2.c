/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:26:46 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 03:27:32 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_data(t_data *data, void **ptr, char *str, t_img *img)
{
	(*ptr) = mlx_xpm_file_to_image(data->mlx.ptr, str, &img->width,
			&img->height);
	if (*ptr == 0)
	{
		write(2, "Error,\nAt least one xpm file is invalid.\n", 41);
		free_images(data);
		exit(0);
	}
}

void	free_images(t_data *data)
{
	if (data->sprite.ptr)
		mlx_destroy_image(data->mlx.ptr, data->sprite.ptr);
	if (data->ciel.ptr)
		mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
	if (data->sol.ptr)
		mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
	if (data->stext.ptr)
		mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	if (data->ntext.ptr)
		mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	if (data->etext.ptr)
		mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	if (data->wtext.ptr)
		mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
}

void	free_path(t_data *data)
{
	if (data->parse.no_tex)
		free(data->parse.no_tex);
	if (data->parse.so_tex)
		free(data->parse.so_tex);
	if (data->parse.we_tex)
		free(data->parse.we_tex);
	if (data->parse.ea_tex)
		free(data->parse.ea_tex);
	if (data->parse.sprite_tex)
		free(data->parse.sprite_tex);
	if (data->parse.sky_tex)
		free(data->parse.sky_tex);
	if (data->parse.floor_tex)
		free(data->parse.floor_tex);
}
