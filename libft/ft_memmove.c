/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:07:28 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:54 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*copies n bytes from memory area src to memory area dest.
The memory areas may overlap*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	i = 0;
	pdest = (unsigned char *) dest;
	psrc = (unsigned char *) src;
	if (pdest < psrc)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			pdest[i] = psrc[i];
		}
	}
	return (dest);
}
