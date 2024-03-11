/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:50:52 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/05 15:32:33 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_first_child(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.array_commands = ft_parsing(argv[2]);
	if (!pipex.array_commands)
		ft_errors("Pipex: command not foud");
	pipex.command_path = get_cmd(pipex.array_paths, pipex.array_commands[0]);
	if (!pipex.command_path)
	{
		ft_free_array(pipex.array_commands);
		free (pipex.array_paths);
		ft_errors("Pipex: command not foud");
	}
	close(pipex.tube[READ_END]);
	dup2(pipex.tube[WRITE_END], STDOUT_FILENO);
	close(pipex.tube[WRITE_END]);
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.infile);
	if (execve(pipex.command_path, pipex.array_commands, envp) == -1)
		ft_errors("Error: fallo en execve");
}

void	ft_last_child(t_pipex pipex, int argc, char *argv[], char *envp[])
{
	pipex.array_commands = ft_parsing(argv[argc - 2]);
	if (!pipex.array_commands)
		ft_errors("Pipex: command not foud");
	pipex.command_path = get_cmd(pipex.array_paths, pipex.array_commands[0]);
	if (!pipex.command_path)
	{
		free (pipex.array_paths);
		ft_free_array(pipex.array_commands);
		ft_errors("Pipex: command not foud");
	}
	close(pipex.tube[WRITE_END]);
	dup2(pipex.tube[READ_END], STDIN_FILENO);
	close(pipex.tube[READ_END]);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.outfile);
	if (execve(pipex.command_path, pipex.array_commands, envp) == -1)
		ft_errors("Error: fallo en execve");
	ft_responsible_parent(&pipex);
}

void	ft_responsible_parent(t_pipex *pipex)
{
	ft_free_array(pipex->array_paths);
	close(pipex->tube[READ_END]);
	close(pipex->tube[WRITE_END]);
	close(pipex->infile);
	close(pipex->outfile);
}
