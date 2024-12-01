/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:14:16 by marvin            #+#    #+#             */
/*   Updated: 2024/11/21 17:14:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
#include <readline/readline.h>

void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_err_global = 130;
	(void) sig;
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
