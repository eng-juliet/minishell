/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 17:11:35 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote_length(const char *line, int *i)
{
	int	start;
	int	new_pos;

	start = *i;
	if (!handle_quotes(line, *i, line[*i], &new_pos))
		return (-1);
	*i = new_pos;
	return (*i - start);
}

static int	handle_special_length(const char *line, int *i)
{
	int	len;

	if (line[*i + 1] && ((line[*i] == '>' && line[*i + 1] == '>')
			|| (line[*i] == '<' && line[*i + 1] == '<')))
	{
		len = 2;
		*i += 2;
	}
	else
	{
		len = 1;
		(*i)++;
	}
	return (len);
}

static int	handle_word_length(const char *line, int *i)
{
	int	len;

	len = 0;
	while (line[*i] && !ft_isspace(line[*i]) && !is_special_char(line[*i])
		&& line[*i] != '"' && line[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	return (len);
}

int	token_length(const char *line, int *i)
{
	if (line[*i] == '"' || line[*i] == '\'')
		return (handle_quote_length(line, i));
	else if (is_special_char(line[*i]))
		return (handle_special_length(line, i));
	else
		return (handle_word_length(line, i));
}
