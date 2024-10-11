#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"

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
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_all
{
	t_env_list	*env;
	t_token		*token;
	t_cmd		*cmd;
}	t_all;

# define CHAR_SMALLER_THAN 1
# define CHAR_GREATER_THAN 2
# define PIPE 3
# define DOUBLE_SMALL 4
# define DOUBLE_GREAT 5
# define GENERAL 6
# define COMMAND 7

/*----------------------- SEHLL ----------------------*/

t_cmd	*parser(t_token *t);
t_cmd	*cmd_node(t_token *t, t_cmd *cmd_l);
t_cmd	*new_c_node(t_cmd *c, t_token *t);

int		word_count(t_token *t);

void	cmd_l_free(t_cmd *c);

char	*var_value(char *var);

t_env_list	*envellope(char **env);
t_env_list	*new_node(t_env_list *l);

void	    env_l_free(t_env_list *l);

char	    *var_fetch(t_env_list *e, char *str);
char	    *var_pfetch(t_env_list *e, char *str);

char	**s_split(char const *str, const char charset);
char	*spacer(char *s, t_all *all);

void	type_assign(t_token *t);
void	token_free(t_token *t);
void	spacer_shortcut(char *spac, char *s, int *i, int *j);
void	quote_erase(t_token *l);
void	token_l_free(t_token *t);
void	total_free(t_token *t);

int 	size_count(char *str, t_all *all);
int	    is_command(t_token *t);
int	    not_a_split(char *s, char sep, int index);
int	    simple_quoted(char *s, int index);
int	    sym_check(char *input);
int	    quoted(char *s, int index);


t_token	*token_delete(t_token *t);
t_token	*tokenizer(char	*input, t_all *all);
t_token	*token_node(char **chopped);
t_token	*new_t_node(t_token *l);

/* ------------------- PIPEX_BONUS ------------------- */

char	**ft_split(char const *s, char c);
char	*ft_free_tab(char **argv);

void	pipex(int arc, t_cmd *cmd, char **env);

#endif