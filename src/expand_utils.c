/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:40:08 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/25 17:10:29 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_quote_inner(char *input,
	int *i, t_data *data, char *res)
{
	char	*temp;
	int		start;

	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			temp = handle_dollar(input, i, data);
			res = join_and_free(res, temp);
			free(temp);
		}
		else
		{
			start = (*i)++;
			temp = ft_substr(input, start, 1);
			if (!temp)
			{
				free(res);
				return (NULL);
			}
			res = join_and_free(res, temp);
			free(temp);
		}
	}
	return (res);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

char	*get_word(char *str, int *i)
{
	int	start;

	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

void	insert_split_tokens(t_token *cur, t_token *next, char **words)
{
	int		i;
	t_token	*new_token;

	i = 1;
	free(cur->value);
	cur->value = ft_strdup(words[0]);
	while (words[i])
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			break ;
		new_token->value = ft_strdup(words[i]);
		new_token->type = cur->type;
		new_token->next = next;
		cur->next = new_token;
		cur = new_token;
		i++;
	}
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words && words[i])
		free(words[i++]);
	free(words);
}
