/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:03 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:36 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates memory and returns an array of strings, using
the character ’c’ as a delimiter. The array is null-terminated*/

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	start;
	size_t	wcount;

	start = 0;
	wcount = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		while (s[start] != c && s[start])
			start++;
		wcount++;
	}
	return (wcount);
}

static void	*ft_free(char	**array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static void	*ft_findword(char **array, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = 0;
	i = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while (s[end] != c && s[end])
			end++;
		array[i] = ft_substr(s, start, end - start);
		if (!array[i])
			return (ft_free(array, i));
		i++;
		start = end;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	count = ft_count(s, c);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	ft_findword(array, s, c);
	return (array);
}
