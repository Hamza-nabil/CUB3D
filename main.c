/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:06:03 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 17:01:44 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "config/config.h"

t_all			*getall(t_all *a)
{
	static	t_all all;

	if (a)
		all = *a;
	return (&all);
}

int		main(int ac, char **av)
{
	t_all p;
	int				s_l;
	int				bpp;
	int				end;

	if (ac == 2)
	{
		ft_initall(&p, av[1]);
		p = *getall(NULL);
		write(1, "[starting game ... !]\n", 22);
		p.w.mlx_wind = mlx_new_window(p.w.mlx_ptr, p.resx,  p.resy, "CUB3D");
		p.w.img = mlx_new_image(p.w.mlx_ptr, p.resx,  p.resy);
		p.w.tab_img = (int*)mlx_get_data_addr(p.w.img, &bpp, &s_l, &end);
		floorceil(p.w.tab_img, p.floor, p.ceil, p.resx * p.resy);
		ft_update(&p);
		mlx_put_image_to_window(p.w.mlx_ptr, p.w.mlx_wind , p.w.img, 0,0);
		mlx_hook(p.w.mlx_wind, 2, 0, ft_key, (void *)&p);
		// mlx_hook(p.w.mlx_wind, 3, 0, ft_key, (void *)&p);
		// mlx_loop_hook(p.w.mlx_ptr, ft_update, &p);
		mlx_loop(p.w.mlx_ptr);
	}
	return (0);
}
