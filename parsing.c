#include "pipex.h"

static void	free_all(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
}

static const char	*word_len(const char **s, char c, size_t *len)
{
	const char	*p;
	char		quote;

	while (**s && **s == c)
		(*s)++;
	if (!**s)
		return (NULL);
	if (len)
		*len = 0;
	p = *s;
	quote = 0;
	while (*p && (quote || *p != c))
	{
		if (!quote && (*p == '\'' || *p == '"'))
			quote = *p;
		else if (quote && *p == quote)
			quote = 0;
		else if (len)
			(*len)++;
		p++;
	}
	return (p);
}

static size_t	count_words(const char *s, char c)
{
	size_t		wc;
	size_t		len;
	const char	*next;

	wc = 0;
	next = word_len(&s, c, &len);
	while (next)
	{
		wc++;
		s = next;
		next = word_len(&s, c, &len);
	}
	return (wc);
}

static char	*dup_word(const char **s, char c)
{
	char		*word;
	size_t		i;
	size_t		len;
	char		quote;
	const char	*end;

	end = word_len(s, c, &len);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	quote = 0;
	while (*s != end)
	{
		if (!quote && (**s == '\'' || **s == '"'))
			quote = **s;
		else if (quote && **s == quote)
			quote = 0;
		else
			word[i++] = **s;
		(*s)++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_splitty(char const *s, char c)
{
	char	**arr;
	size_t	wc;
	size_t	i;

	if (!s)
		return (NULL);
	wc = count_words(s, c);
	arr = (char **)malloc((wc + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		arr[i] = dup_word(&s, c);
		if (!arr[i])
		{
			free_all(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}