/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:40:12 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/04 16:05:32 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_apostrophe_split(char *str, t_parsing *par)
{
	par->i++;
	par->array_argv[par->subs] = malloc(sizeof (char)
			* ft_strchrlen(str, 39, par->i) + 1);
	if (!par->array_argv[par->subs])
	{
		ft_free_array(par->array_argv);
		ft_errors("Pipex: parsing fail");
	}
	while (str[par->i] && str[par->i] != 39)
		par->array_argv[par->subs][par->j++] = str[par->i++];
	par->array_argv[par->subs][par->j] = '\0';
}

void	ft_quotation_marks_split(char *str, t_parsing *par)
{
	par->i++;
	par->array_argv[par->subs] = malloc(sizeof (char)
			* ft_strchrlen(str, '"', par->i) + 1);
	if (!par->array_argv[par->subs])
	{
		ft_free_array(par->array_argv);
		ft_errors("Pipex: parsing fail");
	}
	while (str[par->i] && str[par->i] != '"')
		par->array_argv[par->subs][par->j++] = str[par->i++];
	par->array_argv[par->subs][par->j] = '\0';
}

void	ft_else_split(char *str, t_parsing *par)
{
	par->array_argv[par->subs] = malloc(sizeof (char)
			* ft_strchrlen(str, ' ', par->i) + 1);
	if (!par->array_argv[par->subs])
	{
		ft_free_array(par->array_argv);
		ft_errors("Pipex: parsing fail");
	}
	while (str[par->i] && str[par->i] != ' ')
		par->array_argv[par->subs][par->j++] = str[par->i++];
	par->array_argv[par->subs][par->j] = '\0';
}
