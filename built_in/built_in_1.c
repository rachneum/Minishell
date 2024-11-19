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

void	my_export(t_all *all)
{
	t_env_list	*current_var;
	t_env_list	*current_var2;
	t_token		*next_content;
	char		**env_rlt;
	char		**tok_rlt;
	char 		*env_name;
    char 		*env_value;
	char		*tok_name;
	char		*tok_value;
	char		*new_value;
    int         rlt;

	current_var = all->env;
	next_content = all->token->next;
	tok_rlt = ft_split(next_content->content, '=');
	next_content->tok_name = tok_rlt[0];
	next_content->tok_value = tok_rlt[1];
	//printf("TOK NAME: %s\n", next_content->tok_name);
	//printf("TOK VALUE: %s\n", next_content->tok_value);	`
	current_var2 = current_var;
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
	while (current_var2)
	{
		if ((ft_strcmp(tok_rlt[0], current_var2->env_name) == 0) && (ft_strcmp(tok_rlt[1], current_var2->env_value) == 0))
		{
			printf("TOK_RLT[0]: %s\n", tok_rlt[0]);
			printf("ENV_RLT_NAME: %s\n", current_var2->env_name);
			rlt = 0;
			break;
		}
		if ((ft_strcmp(tok_rlt[0], current_var2->env_name) == 0) && (ft_strcmp(tok_rlt[1], current_var2->env_value) != 0))
		{
			rlt = 1;
			break;
		}
		if ((ft_strcmp(tok_rlt[0], current_var2->env_name) != 0))
		{
			rlt = 2;
		}
		current_var2 = current_var2->next;
	}
    if (rlt == 0)
        printf("test0\n");
    if (rlt == 1)
        printf("test1\n");
    if (rlt == 2)
        printf("test2\n");
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
}

void	my_unset(t_all *all)
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