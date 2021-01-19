/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:06:28 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/19 17:11:16 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	ft_color(int *rgb)
{
	return (rgb[2] + rgb[1] * 256 + rgb[0] * pow(256, 2));
}

t_all			*getall(t_all *a)
{
	static	t_all all;

	if (a)
		all = *a;
	return (&all);
}

int				ft_close_game(t_all *p)
{
	int i;

	free(p->sprt.sprites);
	p->sprt.sprites = NULL;
	free(p->sprt.sprt_order);
	p->sprt.sprt_order = NULL;
	i = -1;
	while (++i < p->dim.y)
	{
		free(p->map[i]);
		p->map[i] = NULL;
	}
	free(p->map);
	p->map = NULL;
	write(1, "[The end]...", 13);
	exit(0);
}

void			ft_walldist(t_all *p)
{
	if (p->ray.wallside == 0)
		p->ray.walldist = fabs((p->ray.mapx
				- p->pos.x + (1 - p->ray.stepx) / 2) / p->ray.dir.x);
	else
		p->ray.walldist = fabs((p->ray.mapy
				- p->pos.y + (1 - p->ray.stepy) / 2) / p->ray.dir.y);
	if (!p->ray.walldist)
		p->ray.walldist = 0.1;
}
