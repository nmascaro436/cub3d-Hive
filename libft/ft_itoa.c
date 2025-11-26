/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:57:50 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:28:07 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates memory and returns a string representing the 
integer received as an argument.*/

#include "libft.h"

static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count = 1;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	size_t	intlen;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	intlen = ft_count(nb);
	str = malloc(sizeof(char) * (intlen + 1));
	if (!(str))
		return (NULL);
	str[intlen] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (intlen > 0 && nb != 0)
	{
		intlen--;
		str[intlen] = (nb % 10 + '0');
		nb = nb / 10;
	}
	return (str);
}
