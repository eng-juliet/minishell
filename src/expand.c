/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:43:37 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/25 17:01:07 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(t_token *cur, t_token *next, t_data *data)
{
	char	*expanded;
	char	**words;

	expanded = expand_token_value(cur->value, data);
	words = NULL;
	if (expanded && contains_unquoted_variable(cur->value))
		words = split_on_whitespace(expanded);
	if (expanded && words && words[0])
	{
		insert_split_tokens(cur, next, words);
		free_words(words);
		free(expanded);
	}
	else if (expanded)
	{
		free(cur->value);
		cur->value = expanded;
	}
}

char	**split_on_whitespace(char *str)
{
	char	**words;
	int		word_count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	if (word_count == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		words[j] = get_word(str, &i);
		j++;
	}
	words[j] = NULL;
	return (words);
}

int	contains_unquoted_variable(char *input)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			in_quotes = !in_quotes;
		else if (input[i] == '$' && !in_quotes)
			return (1);
		i++;
	}
	return (0);
}

void	expand(t_token *tokens, t_data *data)
{
	t_token	*cur;
	t_token	*next;

	cur = tokens;
	while (cur)
	{
		next = cur->next;
		expand_token(cur, next, data);
		cur = next;
	}
}
