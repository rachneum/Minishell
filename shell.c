/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:03:52 by rachou            #+#    #+#             */
/*   Updated: 2024/10/14 14:17:33 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	main(int arc, char **arv, char **env)
{
	char		*input;
	char		*prompt;
	t_token		*token;
	t_cmd		*c;
	t_all		*all;
	int			i;

	if (arc == 0)
		return (1);
	input = readline("write something : ");
    if (input == NULL) 
        return(1);
    if (ft_strncmp(input, "exit", ft_strlen(input)) == 0) 
	{
    	free(input);
    	return (1);
    }
    if (*input) 
        add_history(input);
	token = tokenizer(input, all);
	c = parser(token);
	while (c->next != NULL)
	{
		i = 0;
		while (c->cmd[i])
		{
			printf("%s\n", c->cmd[i]);
			i++;
		}
		c = c->next;
	}
   	pipex(arc, c, env);
	clear_history();
	cmd_l_free(c);
	total_free(token);
    return 0;
}
