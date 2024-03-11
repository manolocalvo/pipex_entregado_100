/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mancalvo <mancalvo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:22:22 by mancalvo          #+#    #+#             */
/*   Updated: 2024/03/05 15:31:42 by mancalvo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//# include "../memory-leaks-master/include/memory_leaks.h"

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/*to perror*/
# include <stdio.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*path;
	char	**array_paths;
	char	**array_commands;
	char	*command_path;
}	t_pipex;

typedef struct s_parsing
{
	int		len;
	int		i;
	int		j;
	int		subs;
	char	**array_argv;
	char	**array_cmd;
}	t_parsing;

/* ft_childs.c */
void	ft_first_child(t_pipex pipex, char *argv[], char *envp[]);
void	ft_last_child(t_pipex pipex, int argc, char *argv[], char *envp[]);
void	ft_responsible_parent(t_pipex *pipex);

/* ft_freerror.c */
void	ft_errors(char *str);
void	ft_free_array(char **s);

/* ft_parsing.c */
char	**ft_parsing(char *str);
int		ft_strchrlen(char *str, char c, int i);
void	ft_apostrophe_split(char *str, t_parsing *par);
void	ft_quotation_marks_split(char *str, t_parsing *par);
void	ft_else_split(char *str, t_parsing *par);

/* utils */
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif
