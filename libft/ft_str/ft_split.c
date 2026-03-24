/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:01:06 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/06 12:37:40 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c);
static size_t	ft_word_len(const char *s, char c);
static char		**ft_free_array(char **array, size_t size);

char	**ft_split(const char *s, char c)
{
	char	**array;
	size_t	words;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = ft_calloc(words + 1, sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j++ < words)
	{
		while (s[i] == c)
			i++;
		len = ft_word_len(&s[i], c);
		array[j - 1] = ft_substr(s, i, len);
		if (!array[j - 1])
			return (ft_free_array(array, j - 1));
		i += len;
	}
	return (array);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**ft_free_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(array[i++]);
	free(array);
	return (NULL);
}
