

#include "../../inc/minishell.h"

char	*get_var(char *str, int *skip)
{
	int		len;
	char	*name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = ft_substr(str, 0, len);
	*skip = len;
	return (name);
}

static char	*es_dollar(char *str, int *i, t_es *s, t_shell *shell)
{
	char	*exp;
	char	*tmp;

	exp = expand_var(str, i, shell);
	if (!exp)
	{
		free(s->result);
		return (NULL);
	}
	tmp = ft_strjoin(s->result, exp);
	free(s->result);
	free(exp);
	return (tmp);
}

static void	es_char(char *str, int *i, t_es *s, t_shell *shell)
{
	if (str[*i] == '\'' && !s->dq)
	{
		s->sq = !s->sq;
		(*i)++;
	}
	else if (str[*i] == '"' && !s->sq)
	{
		s->dq = !s->dq;
		(*i)++;
	}
	else if (str[*i] == '\\' && s->dq && str[*i + 1] && escapable_quote(str[*i + 1]))
	{
		(*i)++;
		s->result = wl_append(s->result, str[(*i)++]);
	}
	else if (str[*i] == '$' && !s->sq && str[*i + 1])
		s->result = es_dollar(str, i, s, shell);
	else
		s->result = wl_append(s->result, str[(*i)++]);
}

char	*expand_string(char *str, t_shell *shell)
{
	t_es	s;
	int		i;

	s.result = ft_strdup("");
	s.sq = 0;
	s.dq = 0;
	if (!s.result)
		return (NULL);
	i = 0;
	while (str[i] && s.result)
		es_char(str, &i, &s, shell);
	return (s.result);
}
