/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:01:09 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:28:47 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*allocates memory for an array of nmemb elements, each of size bytes.
Returns a pointer to the allocated memory. The memory is set to zero.*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb != 0 && size > 2147483647 / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
