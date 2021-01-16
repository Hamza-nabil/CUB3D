/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:09:20 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/15 18:32:53 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "config/config.h"

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

static void		del(void *content)
{
	t_all		*a;
	static int	i;

	a = getall(NULL);
	a->map[i] = (char *)content;
	getall(a);
	i++;
}

static void		load_image(t_all *p, t_config conf)
{
	int		s_l;
	int		bpp;
	int		end;
	int		i;
	t_wind	wind;

	i = -1;
	while (++i < 5)
	{
		wind.mlx_wind = mlx_xpm_file_to_image(p->w.mlx_ptr,
				conf.text.t[i], &p->texture[i].w, &p->texture[i].h);
		if (!wind.mlx_wind)
			ft_error("ERROR\ntexture not valid.");
		p->texture[i].data = (int *)mlx_get_data_addr(
				wind.mlx_wind, &bpp, &s_l, &end);
	}
}

void			ft_initall(t_all *p, char *file)
{
	t_config	conf;

	ft_pars(&conf, file);
	p->w.mlx_ptr = mlx_init();
	p->pos = conf.pos;
	p->dir = conf.dir;
	p->plane.x = 0.66 * p->dir.y;
	p->plane.y = 0.66 * p->dir.x;
	p->resx = (int)conf.res.x;
	p->resy = (int)conf.res.y;
	p->dim.x = conf.w;
	p->dim.y = conf.h;
	p->floor = 0;
	p->ceil = 0;
	p->floor += ft_color(conf.text.cf[0]);
	p->ceil += ft_color(conf.text.cf[1]);
	p->map = (char **)malloc(p->dim.y * sizeof(char *));
	getall(p);
	ft_lstclear(&(conf.map), &del);
	load_image(p, conf);
	getall(p);
}
