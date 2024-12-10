/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:06:54 by marvin            #+#    #+#             */
/*   Updated: 2024/10/04 16:22:46 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	g_err_global = 0;

static void	l_reset(t_token *t, t_cmd *c)
{
	token_l_free(t);
	cmd_l_free(c);
}

static int	syntax_exit(char *input, t_all *all)
{
	token_l_free(all->token);
	g_err_global = 2;
	return (1);
}

static int	loop(t_all *all, char *input)
{
	while (1)
	{
		while (1)
		{
			init_signal();
			input = readline("Minishell> ");
			if (input <= 0)
				return (write(1, "exit\n", 6), free(input), 1);
			if (*input)
			{
				add_history(input);
				all->token = tokenizer(input, all);
				if (syntax_police(all->token) && syntax_exit(input, all))
					break ;
				all->cmd = parser(all);
				reset_signal();
				if (all->cmd)
					ft_pipex(all->cmd, all->env, all);
				l_reset(all->token, all->cmd);
			}
			else
				free(input);
		}
	}
}

int	main(int arc, char **arv, char **envp)
{
	char					*input;
	t_all					*all;

	if (arc == 1)
	{
		all = (t_all *)malloc(sizeof(t_all));
		all->env = envellope(envp);
		loop(all, input);
		clear_history();
		env_l_free(all->env);
		free(all);
	}
	else
	{
		printf("Wrong amount of arguments!\n");
	}
	return (0);
}

/*token_list_visualizer(all);
cmd_list_visualizer(all);*/