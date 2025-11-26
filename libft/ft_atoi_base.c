/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:04:48 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/06 11:51:09 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base(char c, int base)
{
	int		i;
	char	*baselow;
	char	*baseup;

	i = 0;
	baselow = "0123456789abcdef";
	baseup = "0123456789ABCDEF";
	while (i < base)
	{
		if (c == baselow[i] || c == baseup[i])
			return (1);
		i++;
	}
	return (0);
}

static int	convert(char c, int res, int base)
{
	if (c >= '0' && c <= '9')
		res = res * base + c - 48;
	else if (c >= 'a' && c <= 'f')
		res = res * base + c - 97 + 10;
	else if (c >= 'A' && c <= 'F')
		res = res * base + c - 65 + 10;
	return (res);
}

int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == '+' )
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_base(str[i], base))
	{
		res = convert(str[i], res, base);
		i++;
	}
	return (res * sign);
}
