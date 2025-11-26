/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:50:43 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:26:50 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* returns a pointer to the last occurrence of the character c in the string s
or null if not found */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *) s;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char) c)
		{
			return ((char *) &str[i]);
		}
		i--;
	}
	if ((unsigned char) c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
