/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 05:10:24 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/26 23:25:53 by gaefourn         ###   ########.fr       */
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

void	norme_main(int ac, char *str, t_data *data)
{
	if (ac < 2 || ac > 3)
	{
		write(2, "Error,\nWrong numbers of argument.\n", 34);
		exit(0);
	}
	if (parse_arg(str, data) == -1)
	{
		write(2, "Error,\nMap file is invalid.\n", 28);
		exit(0);
	}
}

void	check_sound(char *str, t_data *data)
{
	int j;

	j = 1;
	str[0] == 'm' ? 1 : j++;
	str[1] == 'a' ? 1 : j++;
	str[2] == 'p' ? 1 : j++;
	str[3] == 's' ? 1 : j++;
	str[4] == '/' ? 1 : j++;
	str[5] == 'R' ? 1 : j++;
	str[6] == '8' ? 1 : j++;
	str[7] == 'M' ? 1 : j++;
	str[8] == '.' ? 1 : j++;
	str[9] == 'c' ? 1 : j++;
	str[10] == 'u' ? 1 : j++;
	str[11] == 'b' ? 1 : j++;
	str[12] == '\0' ? 1 : j++;
	if (j <= 1)
		data->sound = 1;
}
