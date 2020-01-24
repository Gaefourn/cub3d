/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:43:31 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 02:53:52 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	parse_sky(char *str, t_parse *parse, t_bool *check, t_data *data)
{
	int i;

	i = 1;
	norme_parse_sky(str, check, data);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		parse->sky_col = create_hex(str + i, data);
	}
	else if (str[i] == '.' && str[i + 1] == '/')
	{
		parse->sky_tex = ft_strdup(str + i);
		if (check_folder(parse->sky_tex, data) == -1)
		{
			write(2, "Error,\nSky's texture is invalid.\n", 33);
			if (str)
				free(str);
			free_path(data);
			exit(0);
		}
	}
	*check = TRUE;
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	treat_line(char *src, char *dst, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (src[++i])
	{
		while ((src[i] == ' ' || src[i] == '\t') && src[i])
			i++;
		if (src[i] == '0' || src[i] == '1' || src[i] == '2' || src[i] == '3'
		|| src[i] == '4' || src[i] == '5' || src[i] == '6' || src[i] == 'N' ||
		src[i] == 'S' || src[i] == 'E' || src[i] == 'W')
			dst[j++] = src[i];
		else
		{
			write(2, "Error,\nMap is invalid.\n", 23);
			free(src);
			free(dst);
			free_path(data);
			exit(0);
		}
	}
	dst[j] = '\0';
}

int		strlen_chelou(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' ||
		str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == 'N' ||
		str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			j++;
	}
	return (j);
}

void	read_map(t_data *data, char *buffer)
{
	char	*str;
	int		i;
	int		size;

	i = -1;
	size = strlen_chelou(buffer);
	if (!(str = malloc(sizeof(char) * size + 1)))
		exit(0);
	check_map_line(buffer, data);
	treat_line(buffer, str, data);
	if (data->size_line == 0)
		data->size_line = size;
	if (data->size_line != 0)
		if (ft_strlen(str) != data->size_line)
		{
			write(2, "Error,\nMap isn't a rectangle.\n", 30);
			if (buffer)
				free(buffer);
			while (++i < data->actu_line)
				free(data->map[i]);
			free(data->map);
			free_path(data);
			exit(0);
		}
	data->map[data->actu_line] = str;
}
