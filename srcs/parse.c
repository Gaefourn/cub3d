/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 16:42:55 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 04:26:49 by gaefourn         ###   ########.fr       */
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
	if (str[i] >= '0' && str[i] <= '9')
		r = ft_atoi(str);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		g = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		b = ft_atoi(str + i);
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
		*tex = str + i;
	if (open(*tex, O_RDONLY) == -1)
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
	int		i;

	i = 1;
	if (str[i] != ' ' && str[i] != '\t')
	{
		write(2, "Error\nFloor color or texture's path is invalid.\n", 48);
		if (str)
			free(str);
		exit(0);
	}
	if (*check == TRUE)
	{
		write(2, "Error,\nThere is more than one path for floor.\n", 46);
		if (str)
			free(str);
		exit(0);
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		parse->floor_col = create_hex(str + i);
	}
	else if (str[i] == '.' && str[i + 1] == '/')
	{
		parse->floor_tex = str + i;
		if (open(parse->floor_tex, O_RDONLY) == -1)
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
	int		i;

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
		i = 0;
		if (buffer[i] == 'R')
			parse_res(buffer, parse, &parse->check_res);
		else if (buffer[i] == 'N' && buffer[i + 1] == 'O')
			parse_tex(buffer, &parse->no_tex, &parse->check_no);
		else if (buffer[i] == 'S' && buffer[i + 1] == 'O')
			parse_tex(buffer, &parse->so_tex, &parse->check_so);
		else if (buffer[i] == 'W' && buffer[i + 1] == 'E')
			parse_tex(buffer, &parse->we_tex, &parse->check_we);
		else if (buffer[i] == 'E' && buffer[i + 1] == 'A')
			parse_tex(buffer, &parse->ea_tex, &parse->check_ea);
		else if (buffer[i] == 'S')
			parse_tex(buffer, &parse->sprite_tex, &parse->check_sprite);
		else if (buffer[i] == 'F')
			parse_floor(buffer, parse, &parse->check_floor);
		else if (buffer[i] == 'C')
			parse_sky(buffer, parse, &parse->check_sky);
		else if (buffer[i] == '1' && parse->check_floor == TRUE &&
parse->check_sky == TRUE && parse->check_no == TRUE && parse->check_so == TRUE
&& parse->check_ea == TRUE && parse->check_we == TRUE)
		{
			read_map(data, buffer);
			data->actu_line++;
		}
		else if (check_line(buffer) == 0)
			;
		else
		{
			write(2, "Oops, somethng went wrong lul.\n", 30);
			free(buffer);
			exit(0);
		}
	//	free(buffer);
	}
	if (*buffer)
		free(buffer);
	check_char(data);
	return (0);
}
