/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 16:42:55 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/23 21:33:37 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

long	create_hex(char *str)
{
	int		r;
	int		g;
	int		b;
	int		i;
	long	color;

	i = 0;
	r = 256;
	g = 256;
	b = 256;
	norme_create_hex(str, &r, &g, &b);
	if (!((r >= 0 && r <= 255) || !(g >= 0 && g <= 255)
				|| !(b >= 0 && b <= 255)))
	{
		write(2, "Error,\ncolor is invalid.\n", 26);
		if (str)
			free(str);
		exit(0);
	}
	color = (r << 16) + (g << 8) + b;
	return (color);
}

void	parse_res(char *str, t_parse *parse, t_bool *check)
{
	int	i;

	i = 1;
	if (*check == TRUE)
	{
		write(2, "Error,\nThere is more than one path for a texture.\n", 50);
		if (str)
			free(str);
		exit(0);
	}
	parse->width = ft_atoi(str + i);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		i++;
	parse->height = ft_atoi(str + i);
	if (parse->width <= 0 || parse->height <= 0)
	{
		write(2, "Error,\nInvalid resolution.\n", 27);
		if (str)
			free(str);
		exit(0);
	}
	*check = TRUE;
}

void	parse_tex(char *str, char **tex, t_bool *check)
{
	int	i;

	if (*check == TRUE)
	{
		write(2, "Error,\nThere is more than one path for a texture.\n", 50);
		if (str)
			free(str);
		exit(0);
	}
	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '.' && str[i + 1] == '/')
		*tex = ft_strdup(str + i);
	if (check_folder(*tex) == -1)
	{
		write(2, "Error,\nAt least one texture path is invalid.\n", 45);
		if (str)
			free(str);
		exit(0);
	}
	*check = TRUE;
}

void	parse_floor(char *str, t_parse *parse, t_bool *check)
{
	int	i;

	i = 1;
	norme_parse_floor(str, check);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		parse->floor_col = create_hex(str + i);
	}
	else if (str[i] == '.' && str[i + 1] == '/')
	{
		parse->floor_tex = ft_strdup(str + i);
		if (check_folder(parse->floor_tex) == -1)
		{
			write(2, "Error,\nFloor's texture is invalid.\n", 35);
			if (str)
				free(str);
			exit(0);
		}
	}
	*check = TRUE;
}

int		parse(char *path, t_parse *parse, t_data *data)
{
	char	*buffer;
	int		ret;
	int		fd;

	init_parse(parse);
	fd = open(path, O_RDONLY);
	set_num_line(data, path);
	buffer = NULL;
	if (!(data->map = malloc(sizeof(char *) * data->num_line + 1)))
	{
		write(2, "Error,\nMalloc failed.\n", 21);
		exit(0);
	}
	while ((ret = get_next_line(fd, &buffer)) > 0)
	{
		norme_main_parse2(buffer, parse, data);
		free(buffer);
	}
	if (ret == 0)
		free(buffer);
	check_char(data);
	return (0);
}
