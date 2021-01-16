/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:09:40 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/16 18:45:27 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static void		ft_init(t_config *p)
{
	int i;

	i = -1;
	p->map = NULL;
	p->sprt = NULL;
	while (++i < 5)
		p->text.t[i] = NULL;
	p->h = 0;
	p->w = 0;
	p->pos.x = 0;
	p->pos.y = 0;
	p->sprt = NULL;
}

void			ft_error(char *s)
{
	perror(s);
	exit(-1);
}

static void		get_conf(char *line, int i, t_config *p)
{
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_r(ft_split(line, ' '), &p->res);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		get_text(ft_split(line, ' '), 0, &p->text);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		get_text(ft_split(line, ' '), 1, &p->text);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		get_text(ft_split(line, ' '), 2, &p->text);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		get_text(ft_split(line, ' '), 3, &p->text);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		get_text(ft_split(line, ' '), 4, &p->text);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		get_rgb(&line[i + 1], 0, &p->text);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		get_rgb(&line[i + 1], 1, &p->text);
	else if (line[i])
		ft_error("ERROR\nmap not valid");
}

static void		check_line(char *line, t_config *p)
{
	int			i;
	static int	count;
	static int	map;

	i = -1;
	while (line[++i] == ' ')
		;
	if (line[i] == '1' && count == 8)
	{
		get_map(line, p);
		map = 1;
	}
	else if (!map)
	{
		get_conf(line, i, p);
		if (line[i])
			count++;
		free(line);
	}
	else
		ft_error("ERROR\nmanque de configuration");
}

void			ft_pars(t_config *p, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = -1;
	ft_init(p);
	if ((fd = open(file, O_RDONLY)) > 0)
		while (get_next_line(fd, &line) > 0)
			check_line(line, p);
	else
		ft_error("ERROR\n file error");
	check_line(line, p);
	p->h = ft_lstsize(p->map);
	if (!p->pos.x)
		ft_error("ERROR\nNo player in the map");
	while (line[++i] && (line[i] == '1' || line[i] == ' '))
		;
	if (line[i])
		ft_error("ERROR\nmap not valid");
}
