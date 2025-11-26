/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:54:25 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:28:50 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* erases the data in the n bytes of the memory starting at the location
pointed to by s, by writing zeros
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
