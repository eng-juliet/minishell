/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:42:32 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/25 17:35:01 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_quote(char *input, int *i, t_data *data)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	(*i)++;
	res = handle_double_quote_inner(input, i, data, res);
	if (input[*i] == '"')
		(*i)++;
	return (res);
}

char	*handle_single_quote(char *input, int *i)
{
	int		start;
	char	*quoted;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	quoted = ft_substr(input, start, *i - start);
	if (input[*i] == '\'')
		(*i)++;
	return (quoted);
}

char	*expand_token_value(char *input, t_data *data)
{
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'')
			temp = handle_single_quote(input, &i);
		else if (input[i] == '"')
			temp = handle_double_quote(input, &i, data);
		else if (input[i] == '$')
			temp = handle_dollar(input, &i, data);
		else
			temp = ft_substr(input, i++, 1);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		result = join_and_free(result, temp);
		free(temp);
	}
	return (result);
}

int	is_quoted(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"'
				&& str[len - 1] == '"')))
		return (1);
	return (0);
}
