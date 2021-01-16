/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:10:50 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/15 16:17:31 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static void		add_sprite(t_list **sprt, unsigned int x, unsigned int y)
{
	t_vect *s;

	s = malloc(sizeof(t_vect));
	s->x = x;
	s->y = y;
	ft_lstadd_front(sprt, ft_lstnew(&s));
}

static void		get_dir(char c, t_vect *dir)
{
	if (c == 'N')
	{
		dir->y = 0;
		dir->x = -1;
	}
	else if (c == 'S')
	{
		dir->x = 1;
		dir->y = 0;
	}
	else if (c == 'E')
	{
		dir->x = 0;
		dir->y = -1;
	}
	else
	{
		dir->x = 0;
		dir->y = 1;
	}
}

static void		check_map(char *line, char *last_line, int i, t_config *p)
{
	if (line[ft_strlen(line) - 1] != '1')
		ft_error("ERROR\n\t");
	if (line[i] == ' ' && ((ft_strlen(last_line) > i) &&
			(last_line[i] == '0' || last_line[i] == '2')))
		ft_error("ERROR\nthis\t");
	else if (ft_strchr("02WSEN", line[i]))
		if (ft_strlen(last_line) < i || last_line[i] == ' ' ||
			line[i + 1] == ' ' || line[i - 1] == ' ')
			ft_error("ERROR\nspace hda 02WSEN");
	if (ft_strchr("WSEN", line[i]))
	{
		if (!p->pos.x && !p->pos.y)
		{
			p->pos.x = i;
			p->pos.y = ft_lstsize(p->map);
			line[i] = '0';
		}
		else
			ft_error("ERROR\ntwo player in the map");
		get_dir(line[i], &p->dir);
	}
}

void			get_map(char *line, t_config *p)
{
	int				i;
	char			*last_line;
	static t_list	*last;

	i = -1;
	if (!p->map)
	{
		while (line[++i] && (line[i] == '1' || line[i] == ' '))
			;
		if (line[i])
			ft_error("ERROR\nmap not valid");
	}
	else
	{
		last_line = last->content;
		while (line[++i] && ft_strchr("012WSEN ", line[i]))
			check_map(line, last_line, i, p);
		if (line[i])
			ft_error("ERROR\nmap not valid");
	}
	last = ft_lstnew(line);
	ft_lstadd_back(&p->map, last);
	p->w = MAX(ft_strlen(line), p->w);
}
