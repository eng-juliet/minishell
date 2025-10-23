/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:30:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 02:35:58 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
}

int	handle_special_char(char *line, int *i, int *total_len)
{
	if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>'
			&& line[*i + 1] == '>'))
		*total_len = 2;
	else
		*total_len = 1;
	(*i) += *total_len;
	return (0);
}

int	handle_regular_token(char *line, int *i, int *total_len)
{
	int	seg_len;

	*total_len = 0;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|')
	{
		seg_len = token_length(line, i);
		if (seg_len < 0)
			return (-1);
		*total_len += seg_len;
	}
	return (0);
}
