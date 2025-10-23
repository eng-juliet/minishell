/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:46:24 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/21 14:17:39 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_without_equal(char *arg, t_data *data)
{
	if (!valid_identifier(arg))
	{
		printf("export: %s: not a valid identifier\n", arg);
		return (1);
	}
	else
	{
		if (!var_exist(arg, data))
			add_to_env(arg, data);
	}
	return (0);
}

void	update_env_var(t_data *data, char *var, char *value)
{
	int		i;
	int		len;
	char	*joined;
	int		datalen;

	i = 0;
	len = ft_strlen(var);
	if (!var || !value)
		return ;
	while (data->env[i])
	{
		datalen = ft_strlen(data->env[i]);
		if (ft_strncmp(data->env[i], var, len) == 0
			&& (data->env[i][len] == '='
			|| (data->env[i][len] == '\0' && datalen == len)))
		{
			free(data->env[i]);
			joined = ft_strjoin(var, "=");
			data->env[i] = ft_strjoin(joined, value);
			free(joined);
			return ;
		}
		i++;
	}
}

int	handle_with_equal(char *arg, t_data *data, char *equal)
{
	int		var_len;
	char	*var;
	char	*value;

	var_len = equal - arg;
	var = ft_substr(arg, 0, var_len);
	value = ft_strdup(equal + 1);
	if (!valid_identifier(var) || var_len == 0)
	{
		printf("export: %s: not a valid identifier\n", arg);
		free(var);
		free(value);
		return (1);
	}
	if (var_exist(var, data))
		update_env_var(data, var, value);
	else
		add_to_env(arg, data);
	free(var);
	free(value);
	return (0);
}

void	handle_export_command(char **args, t_data *data)
{
	int		i;
	char	*equal;
	int		error;

	i = 1;
	error = 0;
	if (!args[i])
		print_exported_env(data->env);
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			if (handle_with_equal(args[i], data, equal))
				error = 1;
		}
		else
		{
			if (handle_without_equal(args[i], data))
				error = 1;
		}
		i++;
	}
	data->last_status = error;
}
