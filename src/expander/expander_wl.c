

#include "../../inc/minishell.h"

int	wl_init(t_wlst *s)
{
	s->words = malloc(sizeof(char *));
	if (!s->words)
		return (0);
	s->words[0] = NULL;
	s->cur = ft_strdup("");
	if (!s->cur)
		return (free(s->words), 0);
	s->n = 0;
	s->sq = 0;
	s->dq = 0;
	s->ws = 0;
	return (1);
}

char	*wl_append(char *s, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(s, buf);
	free(s);
	return (tmp);
}

int	wl_add(t_wlst *s)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (s->n + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (i < s->n)
	{
		tmp[i] = s->words[i];
		i++;
	}
	tmp[s->n] = s->cur;
	tmp[s->n + 1] = NULL;
	free(s->words);
	s->words = tmp;
	s->n++;
	s->cur = ft_strdup("");
	s->ws = 0;
	return (s->cur != NULL);
}

static int	wl_ifs_split(char *val, t_wlst *s)
{
	int		j;
	char	*tmp;

	j = 0;
	while (val[j])
	{
		if (is_space(val[j]))
		{
			if ((s->ws || ft_strlen(s->cur) > 0) && !wl_add(s))
				return (0);
			while (val[j] && is_space(val[j]))
				j++;
		}
		else
		{
			tmp = wl_append(s->cur, val[j++]);
			if (!tmp)
				return (0);
			s->cur = tmp;
		}
	}
	return (1);
}

int	wl_dollar(char *str, int *i, t_wlst *s, t_shell *shell)
{
	char	*exp;
	char	*tmp;

	if (s->sq)
		return (0);
	exp = expand_var(str, i, shell);
	if (!exp)
		return (-1);
	if (s->dq)
	{
		tmp = ft_strjoin(s->cur, exp);
		free(s->cur);
		free(exp);
		s->cur = tmp;
		if (!tmp)
			return (-1);
		return (1);
	}
	if (!wl_ifs_split(exp, s))
		return (free(exp), -1);
	free(exp);
	return (1);
}
