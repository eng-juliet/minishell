/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:40:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 20:07:42 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redirection(t_token *token, t_command *cmd)
{
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
	{
		cmd->rdir_flag = 1;
		perror("output redirection error");
	}
	return (0);
}

int	handle_input_redirection(t_token *token, t_command *cmd)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(token->next->value, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->rdir_flag = 1;
		perror("input redirection error");
	}
	return (0);
}

int	handle_append_redirection(t_token *token, t_command *cmd)
{
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND,
			0644);
	if (cmd->outfile == -1)
	{
		cmd->rdir_flag = 1;
		perror("append redirection error");
	}
	return (0);
}

int	handle_heredoc_token(t_token *token, t_command *cmd, t_data *data)
{
	int	fd;

	fd = handle_heredoc(token->next->value, data);
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	if (cmd->infile == -1)
	{
		cmd->rdir_flag = 1;
		perror("heredoc error");
	}
	return (0);
}

void	init_loop(t_command **cmd, t_token **cur, t_token *tokens)
{
	int		argc;
	t_token	*tmp;

	argc = 0;
	init_cmd(cmd);
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND)
			argc++;
		tmp = tmp->next;
	}
	(*cmd)->argv = malloc(sizeof(char *) * (argc + 1));
	if (!(*cmd)->argv)
	{
		free(*cmd);
		*cmd = NULL;
		return ;
	}
	*cur = tokens;
}
