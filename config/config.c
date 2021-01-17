/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:09:40 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/17 18:04:39 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub.h"

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
}

void			ft_error(t_config *p, char *s)
{
	int i;

	i = -1;
	while (++i < 5)
		if (p->text.t[i])
			free(p->text.t[i]);
	if (p->map)
		ft_lstclear(&(p->map), free);
	if (p->sprt)
		ft_lstclear(&(p->sprt), free);
	write(1, s, ft_strlen(s));
	exit(-1);
}

static void		get_conf(char *line, int i, t_config *p)
{
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_r(p, ft_split(line, ' '), &p->res);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		get_text(p, ft_split(line, ' '), 0, &p->text);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		get_text(p, ft_split(line, ' '), 4, &p->text);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		get_text(p, ft_split(line, ' '), 3, &p->text);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		get_text(p, ft_split(line, ' '), 2, &p->text);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		get_text(p, ft_split(line, ' '), 1, &p->text);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		get_rgb(p, &line[i + 1], 0, &p->text);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		get_rgb(p, &line[i + 1], 1, &p->text);
	else if (line[i])
		ft_error(p, "ERROR\n  Type identifier not valid.");
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
	else if (map)
		ft_error(p, "ERROR\nMisconfiguration.");
	else
		ft_error(p, "ERROR\nMAP : Characters not valid.");
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
	{
		perror("ERROR\n Argument ");
		exit(0);
	}
	check_line(line, p);
	close(fd);
	p->h = ft_lstsize(p->map);
	if (!p->pos.x)
		ft_error(p, "ERROR\nMAP : could not find the player.");
	while (line[++i] && (line[i] == '1' || line[i] == ' '))
		;
	if (line[i])
		ft_error(p, "ERROR\nMAP : must be closed.");
}
