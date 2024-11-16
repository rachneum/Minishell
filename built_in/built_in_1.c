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

/*void my_export(t_all *all, const char *arg) {
    char *equal_sign = strchr(arg, '='); // Cherche '=' dans l'argument
    char *name = NULL;
    char *value = NULL;

    // Vérifie si l'argument est bien au format `name=value`
    if (!equal_sign) {
        // Si pas de `=`, on ne fait rien
        return;
    }

    // Extraire `name` et `value`
    name = strndup(arg, equal_sign - arg); // `name` = tout avant '='
    value = strdup(equal_sign + 1);        // `value` = tout après '='

    // Validation du nom de la variable
    if (!is_valid_variable_name(name)) {
        fprintf(stderr, "export: `%s`: not a valid identifier\n", arg);
        free(name);
        free(value);
        return;
    }

    // Vérifie si `name` existe déjà dans l'environnement
    t_env_list *current = all->env;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            // `name` existe déjà : ne rien faire
            free(name);
            free(value);
            return;
        }
        current = current->next;
    }

    // Si `name` n'existe pas, on ajoute `name=value` à l'environnement
    t_env_list *new_node = malloc(sizeof(t_env_list));
    new_node->name = name;
    new_node->value = value;
    new_node->var = malloc(strlen(name) + strlen(value) + 2);
    sprintf(new_node->var, "%s=%s", name, value);
    new_node->next = all->env;
    all->env = new_node;
}*/


void	my_export(t_all *all)
{
	t_env_list	*current_var;
	t_token		*next_content;
	char		**env_result;
	char		**tok_result;
	char 		*env_name;
    char 		*env_value;
	char		*tok_name;
	char		*tok_value;

	current_var = all->env;
	next_content = all->token->next;
	//while (all->token)
	tok_result = ft_split(next_content->content, '=');
	next_content->tok_name = tok_result[0];
	next_content->tok_value = tok_result[1];
	printf("TOK NAME: %s\n", next_content->tok_name);
	printf("TOK VALUE: %s\n", next_content->tok_value);
	while (current_var)
	{
		env_result = ft_split(current_var->var, '=');
		current_var->env_name = env_result[0];
		current_var->env_value = env_result[1];
		//printf("VAR: %s\n", current_var->var);
		//printf("NAME OF VAR: %s\n", current_var->env_name);
		//printf("VALUE OF VAR: %s\n", current_var->env_value);
		current_var = current_var->next;
	}
}

/*void	my_export(t_cmd *cmd, t_all *all)
{
	int	i;

	if (!cmd->cmd[1])
	{
		my_env(cmd, all);
		return ;
	}
	i = 1;
	while (all->env->next != NULL)
		all->env = all->env->next;
	while (cmd->cmd[i] && var_value(cmd->cmd[i]))
	{
		all->env = new_node(all->env);
		all->env->var = cmd->cmd[i];
		i++;
	}
	if (!var_value(cmd->cmd[i]))
		printf("syntax error\n");
}*/

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