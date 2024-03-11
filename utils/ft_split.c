/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:08:53 by mancalvo          #+#    #+#             */
/*   Updated: 2023/10/26 16:47:54 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_freememory(char **array, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		free(array[i]);
	free(array);
}

static int	ft_subs_counter(char *str, char c)
{
	int	i;
	int	subs_count;

	i = 0;
	subs_count = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		subs_count++;
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (subs_count);
}

static char	*ft_sub_filler(char *str, int start, int finish)
{
	char	*sub;
	int		i;

	i = 0;
	sub = malloc (sizeof (char) * (finish - start + 1));
	if (!sub)
		return (NULL);
	while (start < finish)
		sub[i++] = str [start++];
	sub[i] = '\0';
	return (sub);
}

char	**ft_split(char const *str, char c)
{
	char	**subs;
	size_t	i;
	size_t	j;
	int		start;

	subs = malloc (sizeof (char *) * (ft_subs_counter((char *)str, c) + 1));
	if (!subs || !str)
		return (NULL);
	i = -1;
	j = 0;
	start = -1;
	while (++i <= ft_strlen(str))
	{
		if (str[i] != c && start < 0)
			start = i;
		else if ((str[i] == c || i == ft_strlen(str)) && start >= 0)
		{
			subs[j++] = ft_sub_filler((char *)str, start, i);
			if (!subs[j -1])
				return (ft_freememory(subs, j), NULL);
			start = -1;
		}
	}
	subs[j] = NULL;
	return (subs);
}
