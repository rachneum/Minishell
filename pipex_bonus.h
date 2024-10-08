/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:04:34 by rachou            #+#    #+#             */
/*   Updated: 2024/10/08 12:04:37 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

char	**ft_split(char const *s, char c);
char	*ft_free_tab(char **argv);
char	*ft_strjoin(char *s1, char *s2);

int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlen(const char *s);

#endif