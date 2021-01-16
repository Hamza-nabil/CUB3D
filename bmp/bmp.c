/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:53:56 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 19:54:01 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void	set_header(t_bitmap_file_header *bfh,
		t_bitmap_info_header *bih, unsigned short *bf_type, t_all *p)
{
	*bf_type = 0x4d42;
	bfh->bf_reserved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_size = 2 + sizeof(t_bitmap_file_header)
		+ sizeof(t_bitmap_info_header)
		+ p->resx * p->resy * 4;
	bfh->bf_off_bits = 0x36;
	bih->bi_size = sizeof(t_bitmap_info_header);
	bih->bi_width = p->resx;
	bih->bi_height = p->resy;
	bih->bi_planes = 1;
	bih->bi_bit_count = 32;
	bih->bi_compression = 0;
	bih->bi_size_image = 0;
	bih->bi_x_pels_per_meter = 5000;
	bih->bi_y_pels_per_meter = 5000;
	bih->bi_clr_used = 0;
	bih->bi_clr_important = 0;
}

void	set_body(int file, t_all *p, t_bitmap_info_header *bih)
{
	int				x;
	int				y;
	unsigned int	color;

	y = bih->bi_height;
	while (--y >= 0 && (x = -1))
		while (++x < bih->bi_width)
		{
			color = p->w.tab_img[bih->bi_width * y + x];
			write(file, &color, 4);
		}
}

void	write_file(int file, t_all *p)
{
	t_bitmap_file_header	bfh;
	t_bitmap_info_header	bih;
	unsigned short			bf_type;

	set_header(&bfh, &bih, &bf_type, p);
	write(file, &bf_type, sizeof(bf_type));
	write(file, &bfh, sizeof(bfh));
	write(file, &bih, sizeof(bih));
	set_body(file, p, &bih);
}

int		save_bmp(t_all *p)
{
	int						file;

	if (!(file = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)))
	{
		write(1, "Error\nCould not write file", 26);
		return (-1);
	}
	write_file(file, p);
	close(file);
	return (1);
}
