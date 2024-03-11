/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:55:20 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/04 17:47:42 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strchrlen(char *str, char c, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

int	ft_count_subs(char *str, t_parsing *par)
{
	par->i = 0;
	par->subs = 0;
	while (str[par->i])
	{
		while (str[par->i] == ' ' && str[par->i])
			par->i++;
		while (str[par->i] != ' ' && str[par->i])
			par->i++;
		par->subs++;
		if (str[par->i] == '\0')
			return (par->subs);
		par->i++;
	}
	if (par->subs == 0)
		ft_errors("Pipex: empty command");
	return (par->subs);
}

char	**ft_parse_argv(char *str, t_parsing *par)
{
	par->i = 0;
	par->subs = 0;
	while (str[par->i] && par->subs < par->len)
	{
		if (str[par->i] != ' ')
		{
			par->j = 0;
			if (str[par->i] == 39)
				ft_apostrophe_split(str, par);
			else if (str[par->i] == '"')
				ft_quotation_marks_split(str, par);
			else
				ft_else_split(str, par);
			par->subs++;
		}
		par->i++;
	}
	return (par->array_argv);
}

char	**ft_parsing(char *str)
{
	t_parsing	par;

	if (str == NULL)
		return (NULL);
	par.len = ft_count_subs(str, &par);
	par.array_argv = malloc(sizeof (char *) * (par.len + 1));
	if (!par.array_argv)
		return (NULL);
	par.array_argv = ft_parse_argv(str, &par);
	par.array_argv[par.len] = NULL;
	return (par.array_argv);
}
