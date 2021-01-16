/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <hnabil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:37:53 by hnabil            #+#    #+#             */
/*   Updated: 2021/01/14 17:39:34 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vect	ft_add(t_vect v1, t_vect v2)
{
	t_vect v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_vect	ft_multscal(t_vect v1, double sc)
{
	t_vect v;

	v.x = v1.x * sc;
	v.y = v1.y * sc;
	return (v);
}

double	ft_vectlenght(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
