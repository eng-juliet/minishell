/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:49:43 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 17:35:41 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_token **token, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return ;
	}
	new->type = type;
	new->next = NULL;
	if (!*token)
		*token = new;
	else
	{
		temp = *token;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	check_syntax_error(t_token *cur)
{
	if (cur->type == PIPE && (!cur->next || cur->next->type == PIPE))
	{
		if (!cur->next)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if ((cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == APPEND || cur->type == HEREDOC))
	{
		if (!cur->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (cur->next->type != COMMAND)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				cur->next->value);
			return (1);
		}
	}
	return (0);
}

int	is_syntax_error(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (cur)
	{
		if (check_syntax_error(cur))
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	tokenize(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (ft_strcmp(cur->value, "|") == 0)
			cur->type = PIPE;
		else if (ft_strcmp(cur->value, "<") == 0)
			cur->type = REDIR_IN;
		else if (ft_strcmp(cur->value, ">") == 0)
			cur->type = REDIR_OUT;
		else if (ft_strcmp(cur->value, ">>") == 0)
			cur->type = APPEND;
		else if (ft_strcmp(cur->value, "<<") == 0)
			cur->type = HEREDOC;
		else
			cur->type = COMMAND;
		cur = cur->next;
	}
}
