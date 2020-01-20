/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:12:13 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 03:56:38 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*G_BUFFER[100] =
{
	"0000000000011111111111111111111",
	"00000000001000000000000000000001",
	"00000000001000000111110000000001",
	"00000000001000000011100000000001",
	"00000000001000000001000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"1111111111100000000000000000000111111111",
	"1000000000000000111001111100000000000001",
	"1000000000000001111111111110000000000001",
	"1000000000000000111111111100000000000001",
	"1000000000000000011111110000000000000001",
	"1000000000000000000111000000000000000001",
	"1111111111100000000010000000000111111111",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000001111100000001",
	"00000000001000000001000100000001",
	"00000000001000000001000100000001",
	"00000000001000000001001000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001000000000000000000001",
	"00000000001111111100000000000001",
	"00000000001000000000001111111111",
	"1111111111100000000000000000000111111111",
	"1000000001111111111101000111111100000001",
	"1000000001100000000001000100000000000001",
	"1000000000001111111111000100000000000001",
	"1000000000001000000000000100000000000001",
	"1000000000001000000000000000000000000001",
	"1111111111101111111111111111111111111111",
	"00000000001010000100000000000001",
	"00000000001010000000000000000001",
	"00000000001000000100000000000001",
	"00000000001000000111111100000001",
	"00000000001000000000000011110001",
	"00000000001111111111110000010001",
	"00000000001000000000000000010001",
	"00000000001000000000000010000001",
	"00000000001000000000000010000001",
	"00000000001010000000000010000001",
	"00000000001111000000000010000001",
	"00000000001010000000000010000001",
	"1111111111100005246000001111111111111111",
	"1000000000100000000000000000000000000001",
	"1000000000000000000000010000000000006601",
	"100000000010000S000000010000000000666001",
	"1000000000100000000000010000000000066601",
	"1000000000100000000000010000000000006661",
	"1111111111111110111111111111111111111111",
	"11111111111111101111111111111",
	"10000000001100000000000000001",
	"10110000011105055555555510001",
	"10010000000005055555555510001",
	"10110000011155055555555510001",
	"10000000001155051111011110001",
	"11110111111111011100000010001",
	"11110111111111011101010010001",
	"11000000110101011100000010001",
	"10000000000000001100000010001",
	"10000000000000001101010010001",
	"11000000110101011111011110001",
	"11110111111101011111011110001",
	"11111111111111111111111111111"
};

void	set_dir(t_data *data, char c)
{
	data->perso.dir.x = -1 * (c == 'S' ? -1 : c == 'N');
	data->perso.dir.y = -1 * (c == 'E' ? -1 : c == 'O');
	data->perso.planx = 0.66 * (c == 'O' ? -1 : c == 'E');
	data->perso.plany = 0.66 * (c == 'S' ? -1 : c == 'N');
}

void	*ft_init_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (G_BUFFER[i])
		i++;
	if (!(data->map = malloc(sizeof(char*) * i + 1)))
		return (NULL);

	i = 0;
	while (G_BUFFER[i])
	{
		j = 0;
		while (G_BUFFER[i][j])
			j++;
		if (!(data->map[i] = malloc(sizeof(char) * j + 1)))
			return (NULL);
		i++;
	}
	ft_fill_map(data);
	return ((void*)0);
}

void	ft_fill_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (G_BUFFER[i])
	{
		j = 0;
		while (G_BUFFER[i][j])
		{
			data->map[i][j] = G_BUFFER[i][j];
			if (G_BUFFER[i][j] == 'N' || G_BUFFER[i][j] == 'S' ||
					G_BUFFER[i][j] == 'E' || G_BUFFER[i][j] == 'O')
			{
				set_dir(data, G_BUFFER[i][j]);
				data->map[i][j] = '0';
				data->perso.pos.x = (double)i + 0.5;
				data->perso.pos.y = (double)j + 0.5;
			}
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
}
