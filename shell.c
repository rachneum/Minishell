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
	char		*prompt;
	t_token		*tok;
	t_cmd		*c;
	t_all		*all;
	int			i;

	while (1)
	{
		input = readline("write something : ");
		all = (t_all *)malloc(sizeof(t_all));
		if (*input) 
			add_history(input);
		all->env = envellope(envp);
		all->token = tokenizer(input, all);
		all->cmd = parser(all);
		ft_pipe(arc, all->cmd, all->env);
		//token_list_visualizer(all);
		//cmd_list_visualizer(all);

	}
	clear_history();
	total_free(all);
    return 0;
}
