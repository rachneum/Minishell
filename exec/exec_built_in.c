/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:53:47 by rachou            #+#    #+#             */
/*   Updated: 2024/11/14 15:14:49 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	handle_built_in(t_cmd *cmd, t_all *all)
{
	if (built_in_subshell(cmd, all) || built_in_shell(cmd, all))
        return (1);
    return (0); 
}

int	built_in_subshell(t_cmd *cmd, t_all *all)
{
	/*if ((ft_strcmp(cmd->cmd[0], "cd") == 0) && (ft_strlen(cmd->cmd[0]) == 2))
	{
		//printf("1\n");
		my_cd(cmd->cmd, all);
		return (1);
	}*/
	if ((ft_strcmp(cmd->cmd[0], "export") == 0) && (ft_strlen(cmd->cmd[0]) == 6))
	{
		my_export(all);
		return (1);
	}
	/*else if ((ft_strcmp(cmd->cmd[0], "unset") == 0) && (ft_strlen(cmd->cmd[0]) == 5))
	{
		my_unset(all);
		return (1);
	}
	else if ((ft_strcmp(cmd->cmd[0], "exit") == 0) && (ft_strlen(cmd->cmd[0]) == 4))
	{
		my_exit();
		return (1);
	}*/
	return (0);
}

int	built_in_shell(t_cmd *cmd, t_all *all)
{
	/*if ((ft_strcmp(cmd->cmd[0], "echo") == 0) && (ft_strlen(cmd->cmd[0]) == 4))
	{
		my_echo();
		return (1);
	}*/
	if ((ft_strcmp(cmd->cmd[0], "pwd") == 0) && (ft_strlen(cmd->cmd[0]) == 3))
	{
		printf("ahah\n");
		my_pwd(cmd);
		return (1);
	}
	else if ((ft_strcmp(cmd->cmd[0], "env") == 0) && (ft_strlen(cmd->cmd[0]) == 3))
	{
		my_env(cmd, all);
		return (1);
	}
	return(0);
}
