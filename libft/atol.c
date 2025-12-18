/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:35:42 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/12/18 14:31:28 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	i;
	long	sign;
	long	out;

	i = 0;
	sign = 1;
	out = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == 1 && (out > (LONG_MAX - (nptr[i] - '0')) / 10))
			return (LONG_MAX);
		if (sign == -1 && ((-1 * out) < (LONG_MIN + (nptr[i] - '0')) / 10))
			return (LONG_MIN);
		out = out * 10 + nptr[i] - '0';
		i++;
	}
	return (out * sign);
}
