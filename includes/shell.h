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
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include <termios.h>
# include <stdbool.h>

typedef struct s_pair
{
	int	i;
	int	j;
}	t_pair;

typedef struct s_env_list
{
	char				*var;
	struct s_env_list	*next;
	struct s_env_list	*previous;
}	t_env_list;

typedef struct s_token
{
	char			*content;
	char			*input;
	char			*delimiter;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	int				n_redirection;
	int				prev_tube;
	int				tube[2];
	struct s_token	*in_red;
	struct s_token	*out_red;
	struct s_cmd	*next;
	struct s_cmd	*previous;
	int				heredoc_fd;
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

extern int			g_err_global;

/*general functions*/

void		total_free(t_all *all);
int			syntax_police(t_token *tok);

/*environment_list functions*/

t_env_list	*envellope(char **env);
t_env_list	*new_node(t_env_list *l);
void		env_l_free(t_env_list *l);
char		*var_fetch(t_env_list *e, char *str);
char		*var_value(char *var);
char		*var_pfetch(t_env_list *e, char *str);
char		*var_bfetch(t_env_list *e, char *str);
t_env_list	*env_rewinder(t_env_list *e);

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

/*parsing functions*/

int			word_count(t_token *t);
t_cmd		*cmd_node(t_all *all, t_cmd *cmd_l);
t_cmd		*new_c_node(t_cmd *c, t_token *t);
t_cmd		*parser(t_all *all);
void		cmd_l_free(t_cmd *c);
t_token		*redirect_finder(t_token *t, t_cmd *c);
t_token		*in_red(t_token *t, t_cmd *c);
t_token		*out_red(t_token *t, t_cmd *c);

/*built-in functions*/

int			my_pwd(t_all *all);
void		my_unset(t_all *all);
void		my_echo(char **arg);
int			my_cd(char **cmd, t_all *all);
int			my_export(t_all *all, t_cmd *cm);
void		my_env(t_cmd *cmd, t_all *all);
int			my_exit(t_all *all, t_cmd *c);
void		update_equal(char *c, t_env_list *e);
void		update_append(char *c, t_env_list *e);
char		*get_name(t_env_list *env, char *str);
char		*get_value(t_env_list *env, char *str);

/*exec functions*/

int			ft_pipex(t_cmd *cmd, t_env_list *env_list, t_all *all);
int			init_pids_and_count(t_cmd *cmd, pid_t **pids);
int			create_pipe(int tube[2], pid_t *pids, t_cmd *current_cmd);
pid_t		create_fork(void);
void		close_unused_pipes(t_cmd *current_cmd);
void		wait_for_children(pid_t *pids, int cmd_count);
char		**ft_split(char const *s, char c);
char		*get_path(char **cmd, t_env_list *env_list, int i);
char		**env_list_to_array(t_env_list *env_list, int i);
char		*ft_free_tab(char **cmd);
int			ft_strcmp(char *str1, char *str2);
void		handle_redirections(t_cmd *cmd, int *heredoc_fd);
void		handle_input_red(t_token *in_red);
void		handle_append_red(t_token *out_red);
void		handle_output_red(t_token *out_red);
void		handle_heredoc(t_token *in_red, int *heredoc_fd);
int			built_in_subshell(t_cmd *cmd, t_all *all);
int			built_in_shell(t_cmd *cmd, t_all *all);
int	pipes_limit(t_all *all);

/*extra functions*/

void		token_list_visualizer(t_all *all);
void		cmd_list_visualizer(t_all *all);

/*signal functions*/

void		init_signal(void);
void		sigint_handler(int sig);
void		reset_signal(void);

#endif