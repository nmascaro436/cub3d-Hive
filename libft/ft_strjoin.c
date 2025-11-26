/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:07:05 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:25 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates memory and returns a new string, which is the result
of concatenating s1 and s2*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_size;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1) + 1;
	size = s1_size + ft_strlen(s2);
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_size);
	ft_strlcat(dest, s2, size);
	return (dest);
}
