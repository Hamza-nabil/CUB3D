/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:11:18 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/15 18:26:47 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
}

void	cub_ext(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len < 5)
		ft_error("ERROR\nextention");
	else if (!ft_strncmp(ft_substr(map, len - 4, 4), ".cub", 4))
		write(1, "valid\n", 2);
	else
		ft_error("ERROR\nextention");
}

void	get_r(char **line, t_vect *res)
{
	res->x = 2560;
	res->y = 1440;
	if (!line[1] || !line[2] || line[3])
		ft_error("ERROR\nResoluttion");
	else
	{
		if (ft_atoi(line[1]) < 2560)
			res->x = ft_atoi(line[1]);
		if (ft_atoi(line[2]) < 1440)
			res->y = ft_atoi(line[2]);
	}
	free_tab(line);
	if (res->x < 0 || res->y < 0)
		ft_error("ERROR\nResoluttion");
}

void	get_rgb(char *line, int index, t_text *text)
{
	char	**rgb;
	int		i;

	i = -1;
	rgb = ft_split(line, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_tab(rgb);
		ft_error("ERROR\ncolor not valid");
	}
	while (++i < 3)
	{
		text->cf[index][i] = ft_atoi(ft_strtrim(rgb[i], " \t"));
		if (text->cf[index][i] < 0 || text->cf[index][i] > 255)
		{
			free_tab(rgb);
			ft_error("ERROR\ncolor not valid");
		}
	}
	free_tab(rgb);
	free(rgb);
}

void	get_text(char **line, int index, t_text *text)
{
	if (!line[1] || line[2] || text->t[index])
	{
		free_tab(line);
		ft_error("ERROR\nTexture not valid");
	}
	else
		text->t[index] = line[1];
}
