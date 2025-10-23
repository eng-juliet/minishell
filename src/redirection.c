/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:11 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/28 19:50:48 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_token(t_command *cmd, int *i, t_token *token, t_data *data)
{
	if (token->type == REDIR_OUT && token->next && !cmd->rdir_flag)
		return (handle_output_redirection(token, cmd));
	else if (token->type == REDIR_IN && token->next && !cmd->rdir_flag)
		return (handle_input_redirection(token, cmd));
	else if (token->type == APPEND && token->next && !cmd->rdir_flag)
		return (handle_append_redirection(token, cmd));
	else if (token->type == HEREDOC && token->next && !cmd->rdir_flag)
		return (handle_heredoc_token(token, cmd, data));
	else if (token->type == COMMAND)
		cmd->argv[(*i)++] = ft_strdup(token->value);
	return (0);
}

int	process_single_token(t_token **cur, t_command *cmd, int *i, t_data *data)
{
	t_token	*token;
	int		result;

	token = *cur;
	result = handle_token(cmd, i, token, data);
	if (result == -1)
		return (-1);
	if (token->type != COMMAND && token->next)
		*cur = token->next;
	return (0);
}

int	process_command_tokens(t_token **tokens, t_command *tmp, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if (process_single_token(tokens, tmp, &i, data) == -1)
		{
			if (tmp->argv)
			{
				j = 0;
				while (j < i && tmp->argv[j])
					free(tmp->argv[j++]);
				free(tmp->argv);
			}
			free(tmp);
			return (-1);
		}
		*tokens = (*tokens)->next;
	}
	tmp->argv[i] = NULL;
	return (0);
}

t_command	*create_and_init_command(t_token **tokens, t_data *data)
{
	t_command	*tmp;

	tmp = malloc(sizeof(t_command));
	if (!tmp)
		return (NULL);
	ft_initialize_pipe(tmp);
	init_loop(&tmp, tokens, *tokens);
	if (!tmp)
		return (NULL);
	if (process_command_tokens(tokens, tmp, data) == -1)
		return (NULL);
	return (tmp);
}

void	parse_tokens_to_command(t_token *tokens, t_data *data, t_command **cmd)
{
	t_command	*tmp;

	*cmd = NULL;
	while (tokens)
	{
		tmp = create_and_init_command(&tokens, data);
		if (!tmp)
		{
			*cmd = NULL;
			return ;
		}
		add_list_back(cmd, tmp);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
}
