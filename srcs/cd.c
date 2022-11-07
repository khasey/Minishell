/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:09:43 by humartin          #+#    #+#             */
/*   Updated: 2022/11/02 15:35:52 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_something_out(char *oldpwd, t_List *environ, char *path, char *line)
{
	char	*lastslash;
	int		count;
	int		i;

	i = 5;
	count = 1;
	lastslash = NULL;
	ft_strcpy(oldpwd, "OLDPWD=");
	ft_strcat(oldpwd, ft_strcpylen(getat(environ,
				find_env_pos(environ, "PWD=")), "PWD="));
	while (line[i] != '\0' && (line[i] == '/'
			&& line[i + 1] == '.' && line[i + 2] == '.'))
	{
		count += 1;
		i += 3;
	}
	ft_strcpy(path, getat(environ, find_env_pos(environ, "PWD=")));
	path = ft_strcpylen(path, "PWD=");
	while (count > 0)
	{
		lastslash = ft_strrchr(path, '/');
		ft_bzero(lastslash, ft_strlen(lastslash));
		count--;
	}
	built_in_cd(path, environ, oldpwd);
}

t_List	*cd_out(char *oldpwd, t_List *environ, char *path, char *line)
{
	if (line[5] != '.')
	{
		do_something_out(oldpwd, environ, path, line);
		return (environ);
	}
	else
	{
		g_status = 1;
		ft_putstr_fd(RED"error cd\n"RESET, 2);
		return (environ);
	}
}

void	do_something_in(char *oldpwd, t_List *environ, char *path, char *line)
{
	ft_strcpy(oldpwd, "OLDPWD=");
	ft_strcat(oldpwd,
		ft_strcpylen(getat(environ,
				find_env_pos(environ, "PWD=")), "PWD="));
	path = ft_strcpylen(line, "cd /");
	built_in_cd(path, environ, oldpwd);
	g_status = 0;
}

t_List	*cd_in(char *oldpwd, t_List *environ, char *path, char *line)
{
	char	*buff;

	buff = NULL;
	if (line[3] == 47)
	{
		do_something_in(oldpwd, environ, path, line);
	}
	else
	{
		ft_strcpy(oldpwd, "OLDPWD=");
		ft_strcat(oldpwd,
			ft_strcpylen(getat(environ,
					find_env_pos(environ, "PWD=")), "PWD="));
		buff = malloc(sizeof(line));
		ft_strcpy(path, getat(environ, find_env_pos(environ, "PWD=")));
		buff = ft_strcpylen(line, "cd ");
		ft_strcat(path, buff);
		path = ft_strcpylen(path, "PWD=");
		built_in_cd(path, environ, oldpwd);
		g_status = 0;
	}
	return (environ);
}

t_List	*check_cd(char *line, char *str, t_List *environ, int i)
{
	char	*path;
	char	*oldpwd;

	oldpwd = malloc(10000 * sizeof(char));
	path = malloc(10000 * sizeof(char));
	while (line[i] == str[i] && (line[i] != '\0' || str[i] != '\0'))
		i++;
	if (i == 3)
	{
		cd_in(oldpwd, environ, path, line);
		return (environ);
	}
	else if (i == 5)
	{
		cd_out(oldpwd, environ, path, line);
		return (environ);
	}
	else
		return (environ);
}
