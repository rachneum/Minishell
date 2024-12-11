/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:53:47 by rachou            #+#    #+#             */
/*   Updated: 2024/12/11 12:42:04 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	built_in_subshell(t_cmd *cmd, t_all *all)
{
	if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "cd") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 2))
	{
		my_cd(cmd->cmd, all);
		return (1);
	}
	else if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "export") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 6))
	{
		my_export(all, cmd);
		return (1);
	}
	else if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "unset") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 5))
	{
		my_unset(all);
		return (1);
	}
	else if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "exit") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 4))
	{
		my_exit(all, cmd);
		return (1);
	}
	return (0);
}

int	built_in_shell(t_cmd *cmd, t_all *all)
{
	if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "echo") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 4))
	{
		my_echo(cmd->cmd);
		return (1);
	}
	else if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 3))
	{
		my_pwd(all);
		return (1);
	}
	else if (cmd->cmd[0] && (ft_strcmp(cmd->cmd[0], "env") == 0)
		&& (ft_strlen(cmd->cmd[0]) == 3))
	{
		my_env(cmd, all);
		return (1);
	}
	return (0);
}
