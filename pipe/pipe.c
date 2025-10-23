/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:34:16 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 19:13:26 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize_pipe(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->prev_pipe = -1;
	cmd->outfile = -1;
	cmd->infile = -1;
	cmd->pid = 0;
	cmd->next_cmd = NULL;
	cmd->builtin_fun = 0;
	cmd->redirections = NULL;
	cmd->rdir_flag = 0;
}

void	child_sig_c(int sig)
{
	g_last_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	continue_pipe_execute(t_command *cmd, t_data *data)
{
	if (cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
	if (cmd->rdir_flag)
	{
		ft_cleanup(data, NULL);
		exit(1);
	}
	execute_redirection(cmd);
	if (is_builtin(cmd->argv[0]))
	{
		run_builtin(cmd->argv, data);
		ft_cleanup(data, NULL);
		exit(data->last_status);
	}
	else
	{
		get_cmd(cmd, data);
		execve(cmd->full_path, cmd->argv, data->env);
		ft_error(cmd, data, 1);
		exit(126);
	}
}

void	execute_pipeline(t_data *data)
{
	t_command	*current;
	t_command	*last_cmd;

	current = data->cmd;
	last_cmd = current;
	while (current)
	{
		if (current->next)
		{
			if (pipe(current->pipe_fd) == -1)
			{
				perror("pipe");
				return ;
			}
			current->next->prev_pipe = current->pipe_fd[0];
		}
		ft_pipe_execute(current, data);
		last_cmd = current;
		current = current->next;
	}
	wait_for_children(data, last_cmd);
	current = data->cmd;
}
