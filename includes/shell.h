/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomvan- <thomvan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:10:44 by marvin            #+#    #+#             */
/*   Updated: 2024/07/27 14:09:01 by thomvan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>

typedef struct s_env_list
{
	char				*var;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	int				n_redirection;
	char			*heredoc_name;
	struct s_token	*in_red;
	struct s_token	*out_red;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_all
{
	t_env_list	*env;
	t_token		*token;
	t_cmd		*cmd;
}	t_all;

# define SMALLER 1
# define GREATER 2
# define DOUBLE_SMALL 3
# define DOUBLE_GREAT 4
# define PIPE 5
# define GENERAL 6
# define COMMAND 7

/*general functions*/

void		total_free(t_all *all);

/*environment_list functions*/

t_env_list	*envellope(char **env);
t_env_list	*new_node(t_env_list *l);
void		env_l_free(t_env_list *l);
char		*variable_fetch(t_env_list *e, char *str);
char		*var_value(char *var);
char		*var_pfetch(t_env_list *e, char *str);
void		env_n_free(t_env_list *t);
t_env_list	*env_node_delete(t_env_list *env);

/*token functions*/

t_token		*new_t_node(t_token *l);
void		token_l_free(t_token *t);
t_token		*token_node(char **chopped);
int			sym_check(char *input);
int			size_count(char *str, t_all *all);
char		*spacer(char *s, t_all *all);
t_token		*tokenizer(char	*input, t_all *all);
void		type_assign(t_token *t);
int			is_command(t_token *t);
t_token		*token_delete(t_token *t);
void		token_free(t_token *t);
int			quoted(char *s, int index);
int			not_a_split(char *s, char sep, int index);
char		**s_split(char const *str, const char charset);
void		quote_erase(t_token *l);
void		spacer_shortcut(char *spac, char *s, int *i, int *j);
int			simple_quoted(char *s, int index);
void		spacer_shortcut(char *spac, char *s, int *i, int *j);

/*parsing functions*/

int			word_count(t_token *t);
t_cmd		*cmd_node(t_token *t, t_cmd *cmd_l);
t_cmd		*new_c_node(t_cmd *c, t_token *t);
t_cmd		*parser(t_token *t);
void		cmd_l_free(t_cmd *c);
t_token		*redirect_finder(t_token *t, t_cmd *c);
t_token		*in_red(t_token *t, t_cmd *c);
t_token		*out_red(t_token *t, t_cmd *c);

/*built-in functions*/

void		my_unset(t_all *all);
void		my_pwd(void);
void		my_echo(char **arg);
void		my_cd(char **cmd);
void		my_export(t_all *all, t_cmd *c);
void		my_env(t_all *all, t_cmd *cmd);

/*extra functions*/

void		token_list_visualizer(t_all *all);
void		cmd_list_visualizer(t_all *all);

/*exec functions*/

void	ft_pipe(int arc, t_cmd *cmd, t_env_list *env_list);
void    child_pipe_redirect(t_cmd *current_cmd, int *tube, int prev_tube, t_env_list *env_list);
void	ft_exec(char **cmd, t_env_list *env_list);

char	*get_path(char **cmd, t_env_list *env_list, int i);
int		check_path(t_env_list *env_list);
char	**env_list_to_array(t_env_list *env_list, int i);
char	*ft_free_tab(char **cmd);

char	**ft_split(char const *s, char c);
char	**ft_split_wds(char const *s, char c, char **dst, int num_wds);
char	**ft_free_split(char **ptr, int i);
char	*ft_put(char *wds, char const *s, int i, int len_wds);
int		ft_cnt_wds(char const *str, char c);

//char 	*handle_heredoc(char *delimiter);
void    handle_redirections(t_cmd   *cmd);


#endif