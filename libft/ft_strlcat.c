/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:41:47 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:23 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*concatenates src to the end of dst, taking the full size of the buffer and
guarantee to null terminate. Returns the length of the string tried to create*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ld = 0;
	while (dst[ld] && ld < size)
	{
		ld++;
	}
	ls = ft_strlen(src);
	if (ld == size)
		return (size + ls);
	i = 0;
	while (src[i] && ld + i < size - 1)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
