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

int	main(int arc, char **arv, char **env)
{
	char		*input;
	char		*prompt;
	t_token		*token;
	t_cmd		*c;
    t_all       *all;
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
    while (c->previous != NULL)
        c = c->previous;
    ft_pipe(arc, c, env);
	clear_history();
	cmd_l_free(c);
	total_free(token);
    return 0;
}
