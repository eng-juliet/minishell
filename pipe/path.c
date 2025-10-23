/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:05:51 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 02:54:19 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_access(t_command *cmd, t_data *data)
{
	if (access(cmd->argv[0], F_OK) == 0)
	{
		if (access(cmd->argv[0], R_OK | X_OK) == 0)
		{
			cmd->full_path = ft_strdup(cmd->argv[0]);
			if (!cmd->full_path)
			{
				if (cmd->path)
					free_argv(cmd->path);
				cmd->path = NULL;
				ft_error(cmd, data, 127);
			}
			return ;
		}
		if (cmd->path)
			free_argv(cmd->path);
		cmd->path = NULL;
		ft_error(cmd, data, 126);
	}
	if (cmd->path)
		free_argv(cmd->path);
	cmd->path = NULL;
	ft_error(cmd, data, 128);
}

int	check_path_access(t_command *cmd, t_data *data)
{
	data->slash = ft_strjoin(cmd->path[cmd->i], "/");
	if (!data->slash)
	{
		free_argv(cmd->path);
		cmd->path = NULL;
		ft_error(cmd, data, 127);
	}
	cmd->full_path = ft_strjoin(data->slash, cmd->argv[0]);
	free(data->slash);
	if (!cmd->full_path)
	{
		free_argv(cmd->path);
		cmd->path = NULL;
		ft_error(cmd, data, 127);
	}
	if (access(cmd->full_path, F_OK) == 0)
	{
		if (access(cmd->full_path, R_OK | X_OK) == 0)
			return (1);
		free_argv(cmd->path);
		cmd->path = NULL;
		ft_error(cmd, data, 126);
	}
	return (0);
}

void	get_cmd_path(t_command *cmd, t_data *data)
{
	cmd->i = 0;
	find_path(cmd, data);
	while (cmd->path[cmd->i])
	{
		if (check_path_access(cmd, data))
			return ;
		if (cmd->full_path)
			free(cmd->full_path);
		cmd->full_path = NULL;
		cmd->i++;
	}
	free_argv(cmd->path);
	cmd->path = NULL;
	ft_error(cmd, data, 127);
}

void	continue_cmd(t_command *cmd, t_data *data, int i)
{
	if (i == (int)ft_strlen(cmd->argv[0]))
	{
		ft_error(cmd, data, 127);
	}
	if (ft_strcmp(cmd->argv[0], ".") == 0)
	{
		ft_putendl_fd(".: filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		ft_error(cmd, data, 2);
	}
	if (ft_strcmp(cmd->argv[0], "..") == 0)
	{
		ft_putendl_fd("..: command not found", STDERR_FILENO);
		ft_error(cmd, data, 127);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		ft_access(cmd, data);
	else
		get_cmd_path(cmd, data);
}

void	get_cmd(t_command *cmd, t_data *data)
{
	int		i;

	i = 0;
	if (!cmd->argv || !cmd->argv[0])
	{
		ft_cleanup(data, NULL);
		exit(0);
		return ;
	}
	while (cmd->argv[0][i] && cmd->argv[0][i] == ' ')
		i++;
	continue_cmd(cmd, data, i);
	i = 0;
	while (cmd->path && cmd->path[i])
	{
		free(cmd->path[i]);
		i++;
	}
	free(cmd->path);
	cmd->path = NULL;
}
