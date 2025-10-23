/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:35:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 19:54:07 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_data *data, t_command *last_cmd)
{
	t_command	*current;
	int			status;
	int			has_children;

	current = data->cmd;
	status = 0;
	has_children = 0;
	while (current)
	{
		if (current->pid > 0)
		{
			has_children = 1;
			waitpid(current->pid, &status, 0);
			if (current == last_cmd)
			{
				if (WIFSIGNALED(status))
				{
					if (WTERMSIG(status) == SIGINT)
						data->last_status = 130;
					else
						data->last_status = 128 + WTERMSIG(status);
				}
				else if (WIFEXITED(status))
					data->last_status = WEXITSTATUS(status);
			}
		}
		current = current->next;
	}
	if (!has_children && g_last_sig == SIGINT)
	{
		data->last_status = 130;
		g_last_sig = 0;
	}
}

void	parent(t_command *cmd)
{
	if (cmd->prev_pipe != -1)
		close (cmd->prev_pipe);
	cmd->prev_pipe = -1;
	if (cmd->infile != -1)
		close (cmd->infile);
	cmd->infile = -1;
	if (cmd->outfile != -1)
		close (cmd->outfile);
	cmd->outfile = -1;
}

void	find_path(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->env)
		ft_error(cmd, data, 127);
	while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5) != 0)
		i++;
	if (!data->env[i])
	{
		cmd->path = NULL;
		ft_error(cmd, data, 127);
	}
	cmd->path = ft_split(data->env[i] + 5, ':');
	if (!cmd->path)
		ft_error(cmd, data, 127);
}
