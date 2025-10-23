/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:57:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/24 16:58:29 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_export_env(t_data *data, char *name)
{
	char	*value;
	int		j;
	int		len;

	value = NULL;
	j = 0;
	len = ft_strlen(name);
	while (data->env && data->env[j])
	{
		if (!ft_strncmp(data->env[j], name, len) && data->env[j][len] == '=')
		{
			value = data->env[j] + len + 1;
			break ;
		}
		j++;
	}
	if (!value)
		value = getenv(name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*handle_dollar_special(char *input, int *i, t_data *data)
{
	char	*name;
	char	*value;

	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_status));
	}
	if (input[*i] == '0')
	{
		(*i)++;
		return (ft_strdup(data->shell_name));
	}
	if (ft_isdigit(input[*i]))
	{
		name = ft_substr(input, *i, 1);
		(*i)++;
		value = find_export_env(data, name);
		free(name);
		return (value);
	}
	return (NULL);
}

static char	*handle_dollar_num(char *input, int *i, t_data *data)
{
	char	*name;
	char	*value;
	int		start;

	if (!ft_isalpha(input[*i]) && input[*i] != '_')
	{
		if (input[*i] == '\0' || ft_isspace(input[*i])
			|| is_special_char(input[*i]))
			return (ft_strdup("$"));
		return (ft_strdup(""));
	}
	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = find_export_env(data, name);
	free(name);
	return (value);
}

char	*handle_dollar(char *input, int *i, t_data *data)
{
	char	*res;

	(*i)++;
	res = handle_dollar_special(input, i, data);
	if (res)
		return (res);
	return (handle_dollar_num(input, i, data));
}

char	*join_and_free(char *a, char *b)
{
	char	*res;

	if (!a && !b)
		return (NULL);
	else if (!a)
		return (ft_strdup(b));
	else if (!b)
		return (ft_strdup(a));
	res = ft_strjoin(a, b);
	free(a);
	a = NULL;
	return (res);
}
