/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 05:19:25 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 03:20:59 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_folder(char *str, t_data *data)
{
	int		ret;
	int		fd;
	char	*buff;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * 2)))
		return (-1);
	buff[1] = '\0';
	ret = read(fd, buff, 1);
	if (ret == -1)
	{
		if (buff)
			free(buff);
		free_path(data);
		return (-1);
	}
	if (buff)
		free(buff);
	return (0);
}

int		parse_arg(char *str, t_data *data)
{
	int		len;

	len = ft_strlen(str);
	check_folder(str, data);
	if (str[len - 1] != 'b' && str[len - 2] != 'u' && str[len - 3] != 'c' &&
			str[len - 4] != '.')
		return (-1);
	return (0);
}

void	first_and_last(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '1')
		{
			write(2, "Error,\nMap is invalid.\n", 23);
			free_path(data);
			free(str);
			i = 0;
			while (i < data->actu_line)
			{
				free(data->map[i]);
				i++;
			}
			exit(0);
		}
		i++;
	}
}

void	check_map_line(char *str, t_data *data)
{
	int	i;
	int check;

	i = 0;
	check = ft_strlen(str);
	if (data->actu_line == 0)
		first_and_last(data, str);
	else if (data->actu_line < data->num_line - 1)
	{
		if (str[check - 1] != '1')
		{
			write(2, "Error,\nMap is invalid.\n", 23);
			free_path(data);
			free(str);
			i = 0;
			while (i < data->actu_line)
			{
				free(data->map[i]);
				i++;
			}
			exit(0);
		}
	}
	else if (data->actu_line == data->num_line - 1)
		first_and_last(data, str);
}

void	norme_parse_res(int *width, int *height)
{
	*width > 2560 ? *width = 2560 : 1;
	*height > 1440 ? *height = 1440 : 1;
}
