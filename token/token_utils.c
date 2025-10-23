/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 17:11:31 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char s)
{
	if (s == ' ' || s == '\t' || s == '\n')
		return (1);
	else
		return (0);
}

int	handle_quotes(const char *line, int i, char quote, int *new_pos)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
	{
		printf("minishell: syntax error: unclosed %c quote\n", quote);
		return (0);
	}
	*new_pos = i + 1;
	return (1);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}
