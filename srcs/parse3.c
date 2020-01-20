/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:37:01 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 04:25:45 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	set_num_line(t_data *data, char *path)
{
	char	*buffer;
	int		ret;
	int		fd;
	int		i;

	buffer = NULL;
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &buffer)) > 0)
	{
		i = 0;
		if (buffer[i] == '1')
			data->num_line++;
		free(buffer);
	}
	if (buffer)
		free(buffer);
}

int		check_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_set_char(t_data *data, char c)
{
	data->perso.dir.x = -1 * (c == 'S' ? -1 : c == 'N');
    data->perso.dir.y = -1 * (c == 'E' ? -1 : c == 'O');
    data->perso.planx = 0.66 * (c == 'O' ? -1 : c == 'E');
    data->perso.plany = 0.66 * (c == 'S' ? -1 : c == 'N');
}

void	check_char(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->num_line)
	{
		j = 0;
		while (j < data->size_line)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
			data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				ft_set_char(data, data->map[i][j]);
				data->map[i][j] = '0';
				data->perso.pos.x = (double)i + 0.5;
				data->perso.pos.y = (double)j + 0.5;
			}
			j++;
		}
		i++;
	}
}

