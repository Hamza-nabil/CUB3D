/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:10:33 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 11:47:43 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "../cub3D.h"

typedef struct		s_text
{
	char			*t[5];
	int				cf[2][3];
}					t_text;

typedef struct		s_config
{
	t_vect			res;
	t_text			text;
	t_list			*map;
	t_list			*sprt;
	unsigned int	h;
	unsigned int	w;
	t_vect			pos;
	t_vect			dir;

}					t_config;

void				ft_pars(t_config *p, char *file);
void				get_r(char **line, t_vect *res);
void				get_rgb(char *line, int index, t_text *text);
void				get_text(char **line, int index, t_text *text);
void				cub_ext(char *map);
void				ft_error(char *s);
void				get_map(char *line, t_config *p);

#endif
