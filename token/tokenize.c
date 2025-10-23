/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:00:08 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/21 14:36:19 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_token(char *line, int *i, t_token **head, t_token **current)
{
	int		total_len;
	int		start;
	t_token	*new_token;

	start = *i;
	if (is_special_char(line[*i]))
		handle_special_char(line, i, &total_len);
	else
	{
		if (handle_regular_token(line, i, &total_len) < 0)
			return (-1);
	}
	if (total_len == 0)
	{
		return (0);
	}
	new_token = create_token_node(line, start + total_len, total_len);
	if (!new_token)
		return (-1);
	link_token(head, current, new_token);
	return (0);
}

t_token	*split_line_to_words(char *line)
{
	int		i;
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	current = NULL;
	if (!line || !*line)
		return (NULL);
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (process_token(line, &i, &head, &current) < 0)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
