/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:06:21 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 04:38:37 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(const char *nptr)
{
	int nb;
	int i;
	int neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\r' ||
			nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = ((nb * 10) + (nptr[i] - 48));
		i++;
	}
	if (neg > 0)
		return (-nb);
	return (nb);
}

double	ft_abs(double nb)
{
	(nb < 0) ? nb = nb * -1 : 1;
	return (nb);
}
