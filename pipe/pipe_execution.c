/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:14:01 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/28 19:53:49 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_everything(int saved_stdin, int saved_stdout, int saved_stderr)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close(saved_stderr);
}

static int	run_builtin_in_parent(t_command *cmd, t_data *data)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;
	int	saved_stderr;

	status = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1 || saved_stderr == -1)
	{
		ft_error(cmd, data, 1);
		return (1);
	}
	execute_redirection(cmd);
	if (cmd->rdir_flag)
	{
		close_everything(saved_stdin, saved_stdout, saved_stderr);
		return (1);
	}
	run_builtin(cmd->argv, data);
	status = data->last_status;
	close_everything(saved_stdin, saved_stdout, saved_stderr);
	return (status);
}

static void	exec_child_path(t_command *cmd, t_data *data)
{
	if (cmd->prev_pipe != -1)
	{
		dup2(cmd->prev_pipe, STDIN_FILENO);
		close(cmd->prev_pipe);
	}
	if (cmd->next)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	continue_pipe_execute(cmd, data);
}

static void	exec_parent_path(t_command *cmd)
{
	set_signals_after_child();
	g_last_sig = 0;
	cmd->rdir_flag = 0;
	if (cmd->prev_pipe != -1)
		close(cmd->prev_pipe);
	if (cmd->next)
		close(cmd->pipe_fd[1]);
	parent(cmd);
}

void	ft_pipe_execute(t_command *cmd, t_data *data)
{
	if (is_builtin(cmd->argv[0]) && cmd->prev_pipe == -1 && !cmd->next)
	{
		set_signals_after_child();
		cmd->rdir_flag = 0;
		g_last_sig = 0;
		data->last_status = run_builtin_in_parent(cmd, data);
		if (g_last_sig == SIGINT)
		{
			data->last_status = 130;
			g_last_sig = 0;
		}
		parent(cmd);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_error(cmd, data, 1);
	if (cmd->pid == 0)
	{
		set_signals_child();
		exec_child_path(cmd, data);
	}
	else
		exec_parent_path(cmd);
}
