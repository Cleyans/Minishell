/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:38:05 by brclemen          #+#    #+#             */
/*   Updated: 2024/04/08 17:12:14 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbmots(const char *s, char c)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			count++;
			while (s[index] != '\0' && s[index] != c)
				index++;
		}
		else
			index++;
	}
	return (count);
}

static char	*extrairemots(const char *s, char c, size_t *start)
{
	size_t	index;
	char	*word;

	index = 0;
	while (s[*start + index] != '\0' && s[*start + index] != c)
		index++;
	word = (char *)malloc(index + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + *start, index + 1);
	*start += index;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	mots;
	size_t	start;

	mots = 0;
	start = 0;
	if (!(char *)s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (nbmots(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[start] != '\0')
	{
		if (s[start] == c)
			start++;
		else
		{
			tab[mots] = extrairemots(s, c, &start);
			if (!tab[mots])
				return (NULL);
			mots++;
		}
	}
	tab[mots] = NULL;
	return (tab);
}
