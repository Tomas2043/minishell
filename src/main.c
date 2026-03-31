/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomas <tomas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:58:52 by tomas             #+#    #+#             */
/*   Updated: 2026/03/31 23:25:20 by tomas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	t_env	*current;
	char	**array;
	int		i;

	(void)ac;
	(void)av;
	env = init_env(envp);
	current = NULL;
	array = NULL;
	i = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		if (ft_strcmp(line, "clear") == 0)
			printf("\033[H\033[J");
		else if (ft_strcmp(line, "printenv") == 0)
		{
			current = env;
			while (current)
			{
				printf("%s=%s\n", current->key, current->value);
				current = current->next;
			}
		}
		else if (ft_strcmp(line, "test_set") == 0)
			set_env(&env, "MYVAR", "hello");
		else if (ft_strcmp(line, "test_get") == 0)
			printf("HOME=%s\n", get_env(env, "HOME"));
		else if (ft_strcmp(line, "test_remove") == 0)
			remove_env(&env, "MYVAR");
		else if (ft_strcmp(line, "test_array") == 0)
		{
			array = env_to_array(env);
			i = 0;
			while (array[i])
			{
				printf("%s\n", array[i]);
				i++;
			}
			free_env_array(array);
		}
		free(line);
	}
	free_list(env);
	return (0);
}
