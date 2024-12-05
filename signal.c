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
#include <termios.h>

static void	sigint_handler2(int sig)
{
	g_err_global = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

static void	sigquit_handler(int sig)
{
	g_err_global = 131;
	write(2, "Quit: 3\n", 8);
	(void) sig;
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signal(void)
{
	struct termios	term;

	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, sigquit_handler);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
