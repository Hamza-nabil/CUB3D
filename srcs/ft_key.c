/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:26:12 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/19 16:53:27 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	floorceil(int *tab, unsigned int floor, unsigned int ceil, int size)
{
	int	i;

	i = -1;
	while (++i < size / 2)
		tab[i] = floor;
	while (++i < size)
		tab[i] = ceil;
}

void	ft_rot(t_all *p, double rotspeed)
{
	double old;

	rotspeed *= ROTSPEED;
	old = p->dir.x;
	p->dir.x = p->dir.x * cos(rotspeed) - p->dir.y * sin(rotspeed);
	p->dir.y = old * sin(rotspeed) + p->dir.y * cos(rotspeed);
	old = p->plane.x;
	p->plane.x = p->plane.x * cos(rotspeed) - p->plane.y * sin(rotspeed);
	p->plane.y = old * sin(rotspeed) + p->plane.y * cos(rotspeed);
}

void	ft_mov(t_all *p, t_vect v, double movespeed)
{
	movespeed *= MOVSPEED;
	if (p->map[(int)(p->pos.y)][(int)(p->pos.x + v.x * movespeed)] == '0')
		p->pos.x += v.x * movespeed;
	if (p->map[(int)(p->pos.y + v.y * movespeed)][(int)(p->pos.x)] == '0')
		p->pos.y += v.y * movespeed;
}

int		ft_key(t_all *p)
{
	if (p->mv.fw)
		ft_mov(p, p->dir, p->mv.fw);
	if (p->mv.bk)
		ft_mov(p, p->dir, -p->mv.bk);
	if (p->mv.r)
		ft_mov(p, p->plane, p->mv.r);
	if (p->mv.l)
		ft_mov(p, p->plane, -p->mv.l);
	if (p->mv.rl)
		ft_rot(p, p->mv.rl);
	if (p->mv.rr)
		ft_rot(p, -p->mv.rr);
	ft_update(p);
	mlx_put_image_to_window(p->w.mlx_ptr, p->w.mlx_wind, p->w.img, 0, 0);
	return (0);
}
