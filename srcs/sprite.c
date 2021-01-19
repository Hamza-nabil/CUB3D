/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:03:07 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/19 17:04:04 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		ft_sort_sprites(t_all *p)
{
	double	distance[p->sprt.nbr];
	int		tmp;
	int		disttmp;
	int		i;

	i = -1;
	while (++i < p->sprt.nbr)
	{
		distance[i] = ((p->pos.x - p->sprt.sprites[i].x) * (p->pos.x -
		p->sprt.sprites[i].x) + (p->pos.y - p->sprt.sprites[i].y) * (p->pos.y -
		p->sprt.sprites[i].y));
		p->sprt.sprt_order[i] = i;
	}
	i = -1;
	while (++i < p->sprt.nbr - 1)
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = p->sprt.sprt_order[i];
			p->sprt.sprt_order[i] = p->sprt.sprt_order[i + 1];
			p->sprt.sprt_order[i + 1] = tmp;
			i = -1;
		}
}

void		ft_sprite_width(t_sprtools *t, t_all *p)
{
	t->sprtw = abs((int)(p->resy / (t->trfy)));
	t->drawsx = -t->sprtw / 2 + t->sprtsx;
	if (t->drawsx < 0)
		t->drawsx = 0;
	t->drawex = t->sprtw / 2 + t->sprtsx;
	if (t->drawex >= p->resx)
		t->drawex = p->resx - 1;
	t->stripe = t->drawsx - 1;
}

void		ft_drawspritelines(t_sprtools *t, t_all *p, double *buffer)
{
	int			y;
	int			d;

	t->stripe--;
	while (++t->stripe < t->drawex)
	{
		t->xtex = (int)(256 * (t->stripe - (-t->sprtw / 2 + t->sprtsx))
				* p->texture[p->ray.textn].w / t->sprtw) / 256;
		if (t->trfy > 0 && t->stripe > 0
				&& t->stripe < p->resx && t->trfy < buffer[t->stripe])
			y = t->drawsy - 1;
		while (++y < t->drawey)
		{
			d = y * 256 - p->resy * 128 + t->sprth * 128;
			t->ytex = ((d * p->texture[p->ray.textn].h) / t->sprth) / 256;
			t->color = p->texture[0].data[
					p->texture[p->ray.textn].w * t->ytex + t->xtex];
			if ((t->color & 0x00FFFFFF) != 0)
				p->w.tab_img[t->stripe + (int)p->resx * y] = t->color;
		}
	}
}

void		ft_sprite_height(t_sprtools *t, t_all *p)
{
	t->sprth = abs((int)(p->resy / (t->trfy)));
	t->drawsy = -t->sprth / 2 + p->resy / 2;
	if (t->drawsy < 0)
		t->drawsy = 0;
	t->drawey = t->sprth / 2 + p->resy / 2;
	if (t->drawey >= p->resy)
		t->drawey = p->resy;
}

void		ft_sprite(t_all *p, double *buffer)
{
	t_vect		sprt;
	t_sprtools	t;
	int			i;

	i = -1;
	ft_sort_sprites(p);
	while (++i < p->sprt.nbr)
	{
		sprt = p->sprt.sprites[p->sprt.sprt_order[i]];
		t.sprtx = sprt.x - p->pos.x;
		t.sprty = sprt.y - p->pos.y;
		t.invdet = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
		t.trfx = t.invdet * (p->dir.y * t.sprtx - p->dir.x * t.sprty);
		t.trfy = t.invdet * (-p->plane.y * t.sprtx + p->plane.x * t.sprty);
		t.sprtsx = (int)((p->resx / 2) * (1 + t.trfx / t.trfy));
		ft_sprite_height(&t, p);
		ft_sprite_width(&t, p);
		ft_drawspritelines(&t, p, buffer);
	}
}
