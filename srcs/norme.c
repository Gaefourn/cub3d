/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 05:10:24 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 02:16:00 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	norme_parse_sky(char *str, t_bool *check, t_data *data)
{
	int i;

	i = 1;
	if (str[i] != ' ' && str[i] != '\t')
	{
		write(2, "Error\nSky color or texture's path is invalid.\n", 46);
		if (str)
			free(str);
		free_path(data);
		exit(0);
	}
	if (*check == TRUE)
	{
		write(2, "Error,\nThere is more than one path for sky.\n", 44);
		if (str)
			free(str);
		free_path(data);
		exit(0);
	}
}

void	norme_parse_floor(char *str, t_bool *check, t_data *data)
{
	int	i;

	i = 1;
	if (str[i] != ' ' && str[i] != '\t')
	{
		write(2, "Error\nFloor color or texture's path is invalid.\n", 48);
		if (str)
			free(str);
		free_path(data);
		exit(0);
	}
	if (*check == TRUE)
	{
		write(2, "Error,\nThere is more than one path for floor.\n", 46);
		if (str)
			free(str);
		free_path(data);
		exit(0);
	}
}
