/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:13:26 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:34 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns a pointer to the first occurrence of the character c in the string s
or null if not found*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *) s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
		{
			return ((char *) &str[i]);
		}
		i++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
