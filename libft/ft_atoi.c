/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnabil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:08:03 by hnabil            #+#    #+#             */
/*   Updated: 2019/10/28 12:10:39 by hnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (res);
}
