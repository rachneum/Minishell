/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:25:55 by rachou            #+#    #+#             */
/*   Updated: 2024/10/07 15:33:15 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int main(int argc, char **argv, char **env)
{
    int i;
    int tube[2];
	int	prev_tube;
    pid_t   pid;

    i = 1;
	prev_tube = -1;
    while (argv[i])
    {
		if (i < argc - 1)//Tant que != dernière cmd.
		{
			if (pipe(tube) == -1)//Crée un pipe.
                ft_error("ERROR: The creation of the pipe has failed!\n");
		}
        if ((pid = fork()) == -1)//Fork à chaque cmd.
            ft_error("ERROR: The creation of the fork has failed!\n");
        if (pid == 0)//Si on se trouve bien dans l'enfant.
        {
			if (i < argc - 1)
			{
				dup2(tube[1], 1);//Redirige écriture dans le pipe.
                close(tube[1]);
			}
			if (i > 1)//Tant que != première cmd.
            {
                dup2(prev_tube, 0);//Redirige lecture du pipe (lire dans le pipe précédent).
                close(prev_tube);
            }
			close(tube[0]);
            ft_exec(argv[i], env);
        }
		if (prev_tube != -1)
            close(prev_tube);
        if (i < argc - 1)
        {
            close(tube[1]);//Ferme l'extrémité d'écriture du pipe dans le parent.
            prev_tube = tube[0];//Conserve l'extrémité de lecture pour la prochaine commande.
        }
        waitpid(pid, NULL, 0);
        i++;
    }
}
