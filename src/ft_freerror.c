/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:14:29 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/05 16:11:58 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_errors(char *str)
{
	perror(str);
	if (ft_strncmp(str, "Infile", 6) == 0)
		exit(0);
	exit(EXIT_FAILURE);
}

void	ft_free_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free (s[i]);
		i++;
	}
	free (s);
}
