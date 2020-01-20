/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:43:31 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 04:02:09 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    parse_sky(char *str, t_parse *parse, t_bool *check)
{
    int     i;

    i = 1;
    if (str[i] != ' ' && str[i] != '\t')
    {
        write(2, "Error\nSky color or texture's path is invalid.\n", 46);
        if (str)
            free(str);
        exit(0);
    }
    if (*check == TRUE)
    {
        write(2, "Error,\nThere is more than one path for sky.\n", 44);
        if (str)
            free(str);
        exit(0);
    }
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] >= '0' && str[i] <= '9')
    {
        parse->sky_col = create_hex(str + i);
    }
    else if (str[i] == '.' && str[i + 1] == '/')
    {
        parse->sky_tex = str + i;
        if (open(parse->sky_tex, O_RDONLY) == -1)
        {
            write(2, "Error,\nSky's texture is invalid.\n", 33);
            if (str)
                free(str);
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

void	treat_line(char *src, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		while ((src[i] == ' ' || src[i] == '\t') && src[i])
			i++;
		if (src[i] == '0' || src[i] == '1' || src[i] == '2' || src[i] == '3'
		|| src[i] == '4' || src[i] == '5' || src[i] == '6' || src[i] == 'N' ||
		src[i] == 'S' || src[i] == 'E' || src[i] == 'W')
		{
			dst[j] = src[i];
			j++;
		}
		else
		{
			write(2, "Error,\nMap is invalid.\n", 23);
			if (dst)
				free (dst);
			exit(0);
		}
		i++;
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
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3'||
			str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == 'N'||
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
	{
		write(2, "Error,\nMalloc failed.\n", 21);
		exit(0);
	}
	treat_line(buffer, str);
	if (data->size_line == 0)
		data->size_line = size;
	if (data->size_line != 0)
		if (ft_strlen(str) != data->size_line)
		{
			write(2, "Error,\nMap isn't a rectangle.\n", 30);
			if (buffer)
				free(buffer);
			while (++i < data->actu_line)
				free(data->map2[i]);
			free(data->map2);
			exit(0);
		}
	data->map2[data->actu_line] = str;
}
