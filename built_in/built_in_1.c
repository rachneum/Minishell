/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:54:44 by marvin            #+#    #+#             */
/*   Updated: 2024/10/10 16:54:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_all	*my_export(t_all *all)
{
	t_env_list	*current_var;
	//t_env_list	*current_var2;
	t_token		*next_content;
	char		**env_rlt;
	char		**tok_rlt;
	char		*new_value;

	current_var = all->env;
	next_content = all->token->next;
	tok_rlt = ft_split(next_content->content, '=');
	next_content->tok_name = tok_rlt[0];
	next_content->tok_value = tok_rlt[1];
	
	while (current_var)
	{
		env_rlt = ft_split(current_var->var, '=');
		current_var->env_name = env_rlt[0];
		current_var->env_value = env_rlt[1];
		//printf("VAR: %s\n", current_var->var);
		//printf("ENV NAME: %s\n", current_var->env_name);
		//printf("ENV VALUE: %s\n", current_var->env_value);
		current_var = current_var->next;
	}
	current_var = all->env;
	while (all->env)
	{
		if ((!ft_strcmp(tok_rlt[0], all->env->env_name)) && (!ft_strcmp(tok_rlt[1], all->env->env_value)))
			break;
		if ((!ft_strcmp(tok_rlt[0], all->env->env_name)) && (ft_strcmp(tok_rlt[1], all->env->env_value) != 0))
		{

			free(all->env->env_value);
			//printf("%s\n", all->env->env_value);
			all->env->env_value = ft_strdup(tok_rlt[1]);
			//printf("%s\n", all->env->var);
			//all->env->var = ft_strjoin(all->env->var, all->env->env_value);
			all->env->env_name = ft_strjoin(all->env->env_name, "=");
			all->env->env_name = ft_strjoin(all->env->env_name, all->env->env_value);
			all->env->var = all->env->env_name;
			break;
		}
		/*if ((ft_strcmp(tok_rlt[0], current_var2->env_name) != 0))
		{
			free(all->env->var);
		}*/
		all->env = all->env->next;
	}
	all->env = current_var;
	return (all);
}

/*void	my_cd(char **cmd, t_all *all)
{
	int			err;
	char*		tmp;
	static char	cwd[1024];	

	err = chdir(cmd[1]);
	if (err == -1)
		perror("chdir :");
	getcwd(cwd, sizeof(cwd));
	tmp = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
	while (ft_strncmp(all->env->var, "PWD", 3) != 0
		&& all->env != NULL)
		all->env = all->env->next;
	if (all->env)
	{
		tmp = strncpy(tmp, "PWD=", 4);
		ft_strlcat(tmp, cwd, ft_strlen(cwd + 4));
		free(all->env->var);
		all->env->var = tmp;
		return ;
	}
	free(tmp);
}*/

void my_unset(t_cmd *cmd, t_all *all)
{
	t_env_list	*current_var;

	current_var = all->env;

	while (current_var)
	{
		printf("ENV_NAME: %s\n", current_var->env_name);
		printf("TOKEN_CONTENT: %s\n", all->token->next->content);
		if (!ft_strncmp(current_var->env_name, all->token->next->content, ft_strlen(all->token->next->content)))
		{
			printf("AHAH");
			return ;
		}
		printf("CURRENT_VAR: %s\n", current_var->var);
		current_var = current_var->next;
	}

    /*t_env_list	*current_var;

	current_var = all->env;
    if (cmd->cmd[2])
    {
        printf("Too many arguments !\n");
        return;
    }
	//printf("Comparing: '%s' with '%s'\n", current_var->env_name, all->token->next->content);
    current_var = current_var->next;
	//printf("CURRENT_VAR_NEXT: %s\n", current_var->var);
	while (current_var)
    {
		printf("CURRENT_VAR_NEXT: %s\n", current_var->var);
        if (!ft_strcmp(current_var->env_name, all->token->next->content))
        {
			printf("WHAT\n");
            //free(current_var->var);
            //free(current_var->env_name);
            //free(current_var->env_value);
            //free(current_var);
            break;
        }
        current_var = current_var->next;
		printf("TOKEN_NAME: %s\n", all->token->next->content);
		printf("ENV_NAME: %s\n", current_var->env_name);
    }*/
}

/*void	my_unset(t_all *all)
{
	if (all->cmd[2])
		return (printf("syntax error", ));
	while (strncmp(all->env->var, all->cmd[1], ft_strlen(all->cmd[1])) != 0
		&& all->env != NULL)
		all->env = all->env->next;
	if (all->env != NULL)
		all->env = env_node_delete(all->env);
}

void	env_n_free(t_env_list *t)
{
	free(t->var);
	free(t);
	return ;
}

t_env_list	*env_node_delete(t_env_list *env)
{
	t_env_list	*tmp;

	if (env->next == NULL && env->previous == NULL)
		return (env_n_free(t), NULL);
	else if (env->previous == NULL)
	{
		tmp = env->next;
		tmp->previous = NULL;
		return (env_n_free(t), tmp);
	}
	else if (env->next == NULL)
	{
		tmp = env->previous;
		env_n_free(t);
		tmp->next = NULL;
		return (NULL);
	}
	else
	{
		tmp = env->next;
		env->previous->next = tmp;
		tmp->previous = env->previous;
		return (env_n_free(t), tmp);
	}
}*/