/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:26:12 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/15 19:00:54 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int		ft_key(int key, t_all *p)
{
	if (key == 53)
	{
		write(1, "[ending game ... !]\n", 19);
		exit(0);
	}
	if (key == 13)
		ft_mov(p, p->dir, 1);
	if (key == 1)
		ft_mov(p, p->dir, -1);
	if (key == 2)
		ft_mov(p, p->plane, 1);
	if (key == 0)
		ft_mov(p, p->plane, -1);
	if (key == 123)
		ft_rot(p, 1);
	if (key == 124)
		ft_rot(p, -1);
	floorceil(p->w.tab_img, p->floor, p->ceil, p->resx * p->resy);
	ft_update(p);
	mlx_put_image_to_window(p->w.mlx_ptr, p->w.mlx_wind, p->w.img, 0, 0);
	return (0);
}
