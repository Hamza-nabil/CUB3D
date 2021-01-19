/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:06:03 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/19 17:08:35 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				ft_press(int key, t_all *p)
{
	if (key == 53)
		ft_close_game(p);
	if (key == 13)
		p->mv.fw = 1;
	if (key == 1)
		p->mv.bk = 1;
	if (key == 2)
		p->mv.r = 1;
	if (key == 0)
		p->mv.l = 1;
	if (key == 123)
		p->mv.rr = 1;
	if (key == 124)
		p->mv.rl = 1;
	return (0);
}

int				ft_rel(int key, t_all *p)
{
	if (key == 53)
		ft_close_game(p);
	if (key == 13)
		p->mv.fw = 0;
	if (key == 1)
		p->mv.bk = 0;
	if (key == 2)
		p->mv.r = 0;
	if (key == 0)
		p->mv.l = 0;
	if (key == 123)
		p->mv.rr = 0;
	if (key == 124)
		p->mv.rl = 0;
	return (0);
}

int				ft_checkext(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len < 5 || !ft_strncmp(ft_substr(map, len - 4, 4), ".cub", 4))
		return (1);
	return (0);
}

void			ft_start(char *file, int save)
{
	t_all	p;
	int		s_l;
	int		bpp;
	int		end;

	ft_initall(&p, file);
	p = *getall(NULL);
	p.w.mlx_wind = mlx_new_window(p.w.mlx_ptr, p.resx, p.resy, "CUB3D");
	p.w.img = mlx_new_image(p.w.mlx_ptr, p.resx, p.resy);
	p.w.tab_img = (int*)mlx_get_data_addr(p.w.img, &bpp, &s_l, &end);
	floorceil(p.w.tab_img, p.floor, p.ceil, p.resx * p.resy);
	ft_update(&p);
	if (save)
	{
		save_bmp(&p);
		write(1, "[saved into cub3D.bmp ... !]\n", 24);
		ft_close_game(&p);
	}
	mlx_put_image_to_window(p.w.mlx_ptr, p.w.mlx_wind, p.w.img, 0, 0);
	write(1, "[The game start ... !]\n", 24);
	mlx_hook(p.w.mlx_wind, 2, (1L << 0), ft_press, (void *)&p);
	mlx_hook(p.w.mlx_wind, 3, (1L >> 1), ft_rel, (void *)&p);
	mlx_hook(p.w.mlx_wind, 17, (1L << 5), ft_close_game, &p);
	mlx_loop_hook(p.w.mlx_ptr, ft_key, &p);
	mlx_loop(p.w.mlx_ptr);
}

int				main(int ac, char **av)
{
	if (ac == 3 && ft_checkext(av[1]) && !ft_strncmp(av[2], "--save", 7))
		ft_start(av[1], 1);
	else if (ac == 2 && ft_checkext(av[1]))
		ft_start(av[1], 0);
	else
		write(2, "Error\n Invalid arguments", 26);
	return (0);
}
