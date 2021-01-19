/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:09:20 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/19 17:06:09 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		del(void *content)
{
	t_all		*a;
	static int	i;

	a = getall(NULL);
	a->map[i] = (char *)content;
	getall(a);
	i++;
}

static void		sprt_del(void *content)
{
	t_all		*a;
	static int	i;

	a = getall(NULL);
	a->sprt.sprites[i] = *(t_vect *)content;
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
			ft_error(&conf, "ERROR\n\ttexture not valid.");
		p->texture[i].data = (int *)mlx_get_data_addr(
				wind.mlx_wind, &bpp, &s_l, &end);
		free(conf.text.t[i]);
	}
}

void			ft_initmov(t_mov *mv)
{
	mv->fw = 0;
	mv->bk = 0;
	mv->r = 0;
	mv->l = 0;
	mv->rr = 0;
	mv->rl = 0;
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
	p->floor = ft_color(conf.text.cf[0]);
	p->ceil = ft_color(conf.text.cf[1]);
	p->sprt.nbr = ft_lstsize(conf.sprt);
	p->map = (char **)malloc(p->dim.y * sizeof(char *));
	p->sprt.sprites = (t_vect *)malloc(p->sprt.nbr * sizeof(t_vect));
	p->sprt.sprt_order = (int *)malloc(p->sprt.nbr * sizeof(int));
	ft_initmov(&p->mv);
	getall(p);
	load_image(p, conf);
	ft_lstclear(&(conf.map), &del);
	ft_lstclear(&(conf.sprt), &sprt_del);
	getall(p);
}
