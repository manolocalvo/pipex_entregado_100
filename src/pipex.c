/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:24:49 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/11 12:41:06 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_init(t_pipex *pipex, int argc, char *argv[])
{
	if (argc != 5)
		ft_errors("Error en número de argumentos");
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		ft_errors("Infile");
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
		ft_errors("Error en outfile");
	if (pipe(pipex->tube) < 0)
		ft_errors("Error en tubería");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	ft_init(&pipex, argc, argv);
	pipex.path = find_path(envp);
	if (!pipex.path)
		ft_errors("Error en path");
	pipex.array_paths = ft_split(pipex.path, ':');
	if (!pipex.array_paths)
		ft_errors("Error split path");
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_errors("Error al crear el hijo1");
	if (pipex.pid1 == 0)
		ft_first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		ft_errors("Error al crear el hijo2");
	if (pipex.pid2 == 0)
		ft_last_child(pipex, argc, argv, envp);
	ft_responsible_parent(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
