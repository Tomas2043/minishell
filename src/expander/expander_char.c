

#include "../../inc/minishell.h"

static int	wl_handle_quote(char *str, int *i, t_wlst *s)
{
	if (str[*i] == '\'' && !s->dq)
	{
		s->sq = !s->sq;
		s->ws = 1;
		(*i)++;
		return (1);
	}
	if (str[*i] == '"' && !s->sq)
	{
		s->dq = !s->dq;
		s->ws = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	wl_handle_escape(char *str, int *i, t_wlst *s)
{
	char	*tmp;

	if (!(str[*i] == '\\' && s->dq && str[*i + 1]
			&& escapable_quote(str[*i + 1])))
		return (0);
	tmp = wl_append(s->cur, str[*i + 1]);
	if (!tmp)
		return (-1);
	s->cur = tmp;
	s->ws = 1;
	*i += 2;
	return (1);
}

static int	expand_wl_char(char *str, int *i, t_wlst *s, t_shell *shell)
{
	char	*tmp;
	int		ret;

	if (wl_handle_quote(str, i, s))
		return (1);
	ret = wl_handle_escape(str, i, s);
	if (ret > 0)
		return (1);
	if (ret < 0)
		return (0);
	if (str[*i] == '$' && str[*i + 1])
	{
		ret = wl_dollar(str, i, s, shell);
		if (ret > 0)
			return (1);
		if (ret < 0)
			return (0);
	}
	tmp = wl_append(s->cur, str[(*i)++]);
	if (!tmp)
		return (0);
	s->cur = tmp;
	s->ws = 1;
	return (1);
}

char	**expand_to_wordlist(char *str, t_shell *shell)
{
	t_wlst	s;
	int		i;

	if (!wl_init(&s))
		return (NULL);
	i = 0;
	while (str[i])
		if (!expand_wl_char(str, &i, &s, shell))
			return (free_split(s.words), free(s.cur), NULL);
	if ((s.ws || ft_strlen(s.cur) > 0) && !wl_add(&s))
		return (free_split(s.words), free(s.cur), NULL);
	free(s.cur);
	return (s.words);
}

int	expand_argv_count(t_cmd *cmd, t_shell *shell)
{
	char	**wl;
	int		i;
	int		total;
	int		j;

	i = 0;
	total = 0;
	while (cmd->argv[i])
	{
		wl = expand_to_wordlist(cmd->argv[i++], shell);
		if (!wl)
			return (-1);
		j = 0;
		while (wl[j++])
			total++;
		free_split(wl);
	}
	return (total);
}
