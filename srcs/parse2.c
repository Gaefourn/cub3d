/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:43:31 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/19 23:46:52 by gaefourn         ###   ########.fr       */
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
        printf("sky color = %lx\n", parse->sky_col);
    }
    else if (str[i] == '.' && str[i + 1] == '/')
    {
        parse->sky_tex = str + i;
        printf("sky texture %s\n", parse->sky_tex);
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
