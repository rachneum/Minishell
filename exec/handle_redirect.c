/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:33:59 by rachou            #+#    #+#             */
/*   Updated: 2024/12/10 16:46:43 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	handle_redirections(t_cmd *cmd)
{
	if (cmd->in_red && cmd->in_red->content)
	{
		if ((cmd->in_red->previous->content)
			&& (ft_strcmp(cmd->in_red->previous->content, "<") == 0)
			&& (ft_strlen(cmd->in_red->previous->content) == 1))
			handle_input_red(cmd->in_red);
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

void handle_redirection_hd(t_cmd *cmd, int *heredoc_fd)
{
    reset_hered();
    handle_heredoc(cmd->in_red, heredoc_fd);
}

