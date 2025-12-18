/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:53:42 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/12/18 14:30:45 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compares strings s1 and s2, at most size n.*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (st1[i] && st2[i] && st1[i] == st2[i] && i < n - 1)
		i++;
	return (st1[i] - st2[i]);
}
