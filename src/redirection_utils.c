/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:55:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 20:02:52 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd)
{
	int			i;
	t_command	*tmp;

	while (cmd)
	{
		i = 0;
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->argv)
		{
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		if (tmp->path)
		{
			i = 0;
			while (tmp->path[i])
				free(tmp->path[i++]);
			free(tmp->path);
		}
		if (tmp->full_path)
			free(tmp->full_path);
		free(tmp);
	}
}

void	execute_redirection(t_command *cmd)
{
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
		cmd->infile = -1;
	}
	else if (cmd->prev_pipe != -1)
	{
		dup2(cmd->prev_pipe, STDIN_FILENO);
		close(cmd->prev_pipe);
		cmd->prev_pipe = -1;
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
		cmd->outfile = -1;
	}
	else if (cmd->pipe_fd[1] != -1)
	{
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = -1;
	}
}

void	init_cmd(t_command **cmd)
{
	(*cmd)->argv = NULL;
	(*cmd)->path = NULL;
	(*cmd)->full_path = NULL;
	(*cmd)->next_cmd = NULL;
	(*cmd)->i = 0;
	(*cmd)->infile = -1;
	(*cmd)->outfile = -1;
	(*cmd)->builtin_fun = 0;
	(*cmd)->pipe_fd[0] = -1;
	(*cmd)->pipe_fd[1] = -1;
	(*cmd)->prev_pipe = -1;
	(*cmd)->pid = 0;
	(*cmd)->redirections = NULL;
	(*cmd)->next = NULL;
}

void	add_list_back(t_command **head, t_command *tmp)
{
	t_command	*temp;

	if (!head || !tmp)
		return ;
	if (*head == NULL)
	{
		*head = tmp;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
	}
}
