/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:11:18 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/17 18:04:42 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub.h"

void	free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
}

void	get_r(t_config *p, char **line, t_vect *res)
{
	res->x = 2560;
	res->y = 1440;
	if (!line[1] || !line[2] || line[3])
		ft_error(p, "ERROR\n\tResoluttion not valid");
	else
	{
		if (ft_atoi(line[1]) < 2560)
			res->x = ft_atoi(line[1]);
		if (ft_atoi(line[2]) < 1440)
			res->y = ft_atoi(line[2]);
	}
	free_tab(line);
	if (res->x < 0 || res->y < 0)
		ft_error(p, "ERROR\n\tResoluttion not valid");
}

void	get_rgb(t_config *p, char *line, int index, t_text *text)
{
	char	**rgb;
	int		i;

	i = -1;
	rgb = ft_split(line, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_tab(rgb);
		ft_error(p, "ERROR\n\tcolor not valid");
	}
	while (++i < 3)
	{
		text->cf[index][i] = ft_atoi(ft_strtrim(rgb[i], " \t"));
		if (text->cf[index][i] < 0 || text->cf[index][i] > 255)
		{
			free_tab(rgb);
			ft_error(p, "ERROR\n\tcolor not valid");
		}
	}
	free_tab(rgb);
	free(rgb);
}

void	get_text(t_config *p, char **line, int index, t_text *text)
{
	if (!line[1] || line[2] || text->t[index])
	{
		free_tab(line);
		ft_error(p, "ERROR\n\tTexture not valid");
	}
	else
		text->t[index] = line[1];
}
