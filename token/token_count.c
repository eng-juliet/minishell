/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/07 18:15:31 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quote_content(const char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

static void	skip_word_content(const char *line, int *i)
{
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '"'
		&& line[*i] != '\'' && !is_special_char(line[*i]))
		(*i)++;
}

int	count_tokens(const char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		count++;
		if (line[i] == '"' || line[i] == '\'')
			skip_quote_content(line, &i);
		else
			skip_word_content(line, &i);
	}
	return (count);
}
