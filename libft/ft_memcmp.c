/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:24:07 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:28:00 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*compares the first n bytes of the memory areas s1 and s2. */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ps1;
	const unsigned char	*ps2;
	size_t				i;

	ps1 = (unsigned char *) s1;
	ps2 = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && ps1[i] == ps2[i])
		i++;
	return (ps1[i] - ps2[i]);
}
