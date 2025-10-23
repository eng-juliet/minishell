/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/10 15:38:42 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_new_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = UNKNOWN;
	new_token->next = NULL;
	return (new_token);
}

static char	*extract_token_value(const char *line, int i, int len)
{
	char	*token_value;

	token_value = malloc(len + 1);
	if (!token_value)
		return (NULL);
	ft_strlcpy(token_value, line + i - len, len + 1);
	return (token_value);
}

t_token	*create_token_node(const char *line, int i, int len)
{
	t_token	*new_token;

	new_token = create_new_token();
	if (!new_token)
		return (NULL);
	new_token->value = extract_token_value(line, i, len);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}
