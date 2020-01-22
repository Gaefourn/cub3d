/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 05:19:25 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 06:22:12 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_folder(char *str)
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
		return (-1);
	}
	if (buff)
		free(buff);
	return (0);
}

int	parse_arg(char *str)
{
	int		len;

	len = ft_strlen(str);
	check_folder(str);
	if (str[len - 1] != 'b' && str[len - 2] != 'u' && str[len - 3] != 'c' &&
			str[len - 4] != '.')
		return (-1);
	return (0);
}
