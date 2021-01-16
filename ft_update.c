/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:03:29 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 18:01:06 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	texture(t_all *p, int x, int start, int end)
{
	int		xtex;
	int		ytex;
	double	texpos;
	double	step;
	int		lineheight;

	lineheight = (int)(p->resy / p->ray.walldist);
	xtex = (int)(p->ray.wallx * (double)p->texture[p->ray.textn].w);
	if (p->ray.wallside == 0 && p->ray.dir.x > 0)
		xtex = p->texture[p->ray.textn].w - xtex - 1;
	if (p->ray.wallside == 1 && p->ray.dir.y < 0)
		xtex = p->texture[p->ray.textn].w - xtex - 1;
	step = 1.0 * p->texture[p->ray.textn].h / lineheight;
	texpos = (start - p->resy / 2 + lineheight / 2) * step;
	while (++start < end)
	{
		ytex = (int)texpos & (p->texture[p->ray.textn].h - 1);
		texpos += step;
		p->w.tab_img[x + (int)p->resx * start] = p->texture[
			p->ray.textn].data[p->texture[p->ray.textn].h * ytex + xtex];
		if (p->ray.wallside == 1)
			p->w.tab_img[x + (int)p->resx * start] /= 2;
	}
}

static void	verline(int x, t_all *p)
{
	int	start;
	int	end;
	int	lineheight;

	lineheight = (int)(p->resy / p->ray.walldist);
	start = -lineheight / 2 + p->resy / 2;
	if (start < 0)
		start = 0;
	end = lineheight / 2 + p->resy / 2;
	if (end >= p->resy)
		end = p->resy - 1;
	start--;
	if (!p->ray.wallside)
	{
		p->ray.wallx = p->pos.y + p->ray.walldist * p->ray.dir.y;
		p->ray.textn = (p->ray.dir.x > 0) ? 0 : 1;
	}
	else
	{
		p->ray.wallx = p->pos.x + p->ray.walldist * p->ray.dir.x;
		p->ray.textn = (p->ray.dir.y >= 0) ? 2 : 3;
	}
	p->ray.textn++;
	p->ray.wallx -= (int)p->ray.wallx;
	texture(p, x, start, end);
}

static void	ft_step(t_all *p)
{
	if (p->ray.dir.x < 0)
	{
		p->ray.stepx = -1;
		p->ray.side.x = (p->pos.x - p->ray.mapx) * p->ray.dist.x;
	}
	else
	{
		p->ray.stepx = 1;
		p->ray.side.x = (p->ray.mapx + 1.0 - p->pos.x) * p->ray.dist.x;
	}
	if (p->ray.dir.y < 0)
	{
		p->ray.stepy = -1;
		p->ray.side.y = (p->pos.y - p->ray.mapy) * p->ray.dist.y;
	}
	else
	{
		p->ray.stepy = 1;
		p->ray.side.y = (p->ray.mapy + 1.0 - p->pos.y) * p->ray.dist.y;
	}
}

static void	ft_dda(t_all *p)
{
	ft_step(p);
	while (p->ray.hit == 0)
	{
		if (p->ray.side.x < p->ray.side.y)
		{
			p->ray.side.x += p->ray.dist.x;
			p->ray.mapx += p->ray.stepx;
			p->ray.wallside = 0;
		}
		else
		{
			p->ray.side.y += p->ray.dist.y;
			p->ray.mapy += p->ray.stepy;
			p->ray.wallside = 1;
		}
		if (p->map[p->ray.mapy][p->ray.mapx] == '1')
			p->ray.hit = 1;
	}
}

int		ft_update(t_all *p)
{
	int		x;
	double	buffer[p->resx];

	x = -1;
	while (++x < p->resx)
	{
		p->ray.x = 2 * x / (double)p->resx - 1;
		p->ray.dir = ft_add(p->dir, ft_multscal(p->plane, p->ray.x));
		p->ray.mapx = (int)p->pos.x;
		p->ray.mapy = (int)p->pos.y;
		p->ray.dist.x = fabs(1 / p->ray.dir.x);
		p->ray.dist.y = fabs(1 / p->ray.dir.y);
		p->ray.hit = 0;
		ft_dda(p);
		if (p->ray.wallside == 0)
			p->ray.walldist = (p->ray.mapx
					- p->pos.x + (1 - p->ray.stepx) / 2) / p->ray.dir.x;
		else
			p->ray.walldist = (p->ray.mapy
					- p->pos.y + (1 - p->ray.stepy) / 2) / p->ray.dir.y;
		verline(x, p);
		buffer[x] = p->ray.walldist;
	}
	ft_sprite(p, buffer);
	return (0);
}
