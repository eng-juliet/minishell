/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:00:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/24 16:15:27 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		free(argv[i++]);
	free(argv);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->shell_name)
	{
		data->shell_name = NULL;
	}
	data->last_status = 0;
}

void	ft_fds(t_command *cmd)
{
	t_command	*current;

	if (!cmd)
		return ;
	current = cmd;
	while (current)
	{
		if (current->pipe_fd[0] != -1)
			close(current->pipe_fd[0]);
		if (current->pipe_fd[1] != -1)
			close(current->pipe_fd[1]);
		if (current->prev_pipe != -1)
			close(current->prev_pipe);
		if (current->infile != -1)
			close(current->infile);
		if (current->outfile != -1)
			close(current->outfile);
		current->outfile = -1;
		current->infile = -1;
		current->prev_pipe = -1;
		current->pipe_fd[0] = -1;
		current->pipe_fd[1] = -1;
		current->rdir_flag = 0;
		current = current->next;
	}
}

void	ft_cleanup(t_data *data, char *line)
{
	if (!data)
		return ;
	ft_fds(data->cmd);
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmd)
	{
		free_command(data->cmd);
		data->cmd = NULL;
	}
	if (line)
		free(line);
	rl_clear_history();
}
