/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:36:36 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/07/25 17:19:06 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates memory and returns a copy of s1 with characters
from set removed from the beginning and the end.*/

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trim = ft_substr(s1, start, end - start + 1);
	free(s1);
	return (trim);
}
