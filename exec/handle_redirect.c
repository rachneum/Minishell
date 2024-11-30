/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/11/30 16:55:03 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_redirections(t_cmd *cmd, int *heredoc_fd)
{
	if (cmd->in_red && cmd->in_red->content)
	{
		if ((cmd->in_red->previous->content)
			&& (ft_strcmp(cmd->in_red->previous->content, "<") == 0)
			&& (ft_strlen(cmd->in_red->previous->content) == 1))
			handle_input_red(cmd->in_red);
		if ((cmd->in_red->previous->content)
			&& (ft_strcmp(cmd->in_red->previous->content, "<<") == 0)
			&& (ft_strlen(cmd->in_red->previous->content) == 2))
			handle_heredoc(cmd->in_red, heredoc_fd);
	}
	if (cmd->out_red && cmd->out_red->content)
	{
		if ((cmd->out_red->previous->content)
			&& (ft_strcmp(cmd->out_red->previous->content, ">") == 0)
			&& (ft_strlen(cmd->out_red->previous->content) == 1))
			handle_output_red(cmd->out_red);
		if ((cmd->out_red->previous->content)
			&& (ft_strcmp(cmd->out_red->previous->content, ">>") == 0)
			&& (ft_strlen(cmd->out_red->previous->content) == 2))
			handle_append_red(cmd->out_red);
	}
}
