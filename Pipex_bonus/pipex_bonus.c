/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:45:58 by rachou            #+#    #+#             */
/*   Updated: 2024/09/27 10:22:25 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec()
{

}

static void pipe_reset(int *pipe_fd)
{

}

static void	pipe_read(char **argv, char **env, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);//lit pas dans le terminal, lit dans le pipe.
	close(pipe_fd[0]);
	ft_exec(argv[], env);
}

static void	pipe_write(char **argv, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);//écrit pas dans le terminal, écrit dans le pipe.
	close(pipe_fd[1]);
	ft_exec(argv[1], env);
}

int	path(char **env)//Vérifie que le PATH existe dans l'env.
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		pipe_fd;
	pid_t	pid;
	
	if (path(env) == 0)
		return (0)
	if (argc <= 1)
		return (0);
	/*else if (argc == 2)
		//argv[1] se trouve dans le tab des cmd? si oui exec.*/
	while (argv)//ajouter condition si != cmd.
	{
		if //(c'est pas la dernière cmd).
			if (pipe(pipe_fd) == -1)//Crée max 2 pipes.
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
			{
				pipe_write(argv, env, pipe_fd);
				//appeler fct qui va reset le pipe: pipe[1] = -1???? est-ce qu'en fermant mon pipe et recréant un après ca suffit pour "clean" le pipe???
				pipe_read(argv, env, pipe_fd);
				
			}
	}
	return (0)
}
