/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:06:03 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 19:51:51 by hnabil           ###   ########.fr       */
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
		write(1, "[saved into save.bmp ... !]\n", 24);
		return ;
	}
	write(1, "[starting game ... !]\n", 22);
	mlx_put_image_to_window(p.w.mlx_ptr, p.w.mlx_wind, p.w.img, 0, 0);
	mlx_hook(p.w.mlx_wind, 2, (1L << 0), ft_key, (void *)&p);
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
