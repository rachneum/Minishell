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

int	main(int arc, char **arv, char **envp)
{
	char		*input;
	t_all		*all;

	if (arc == 1)
	{
		all = (t_all *)malloc(sizeof(t_all));
		all->env = envellope(envp);
		while (1)
		{
			input = readline("Write something here: ");
			if (*input) 
				add_history(input);
			all->token = tokenizer(input, all);
			all->cmd = parser(all);
			ft_pipex(all->cmd, all->env, all);
			//token_list_visualizer(all);
			//cmd_list_visualizer(all);
		}
	clear_history();
	total_free(all);
	}
	else
		printf("Wrong amount of arguments!\n");
    return 0;
}
