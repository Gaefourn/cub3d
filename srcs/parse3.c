/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:37:01 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 06:10:32 by gaefourn         ###   ########.fr       */
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
	if (ret == 0)
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

void	norme_create_hex(char *str, int *r, int *g, int *b)
{
	int i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		*r = ft_atoi(str);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		*g = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		*b = ft_atoi(str + i);
}

int		norme_main_parse(char *buffer, t_parse *parse)
{
	int	i;

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
	else
		return (0);
	return (1);
}

void	norme_main_parse2(char *buffer, t_parse *parse, t_data *data)
{
	int i;

	i = 0;
	if (!(norme_main_parse(buffer, parse)))
	{
		if (buffer[i] == '1' && parse->check_floor == TRUE &&
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
			if (*buffer)
				free(buffer);
			exit(0);
		}
	}
}
