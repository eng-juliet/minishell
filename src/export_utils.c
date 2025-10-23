/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:55:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/24 14:18:18 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

void	print_exported_env(char **env)
{
	int		i;
	char	*equal;
	int		var_len;
	char	*var;
	char	*value;

	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
		{
			var_len = equal - env[i];
			var = ft_substr(env[i], 0, var_len);
			value = equal + 1;
			printf("export -x %s=\"%s\"\n", var, value);
			free(var);
		}
		else
		{
			printf("export -x %s\n", env[i]);
		}
		i++;
	}
}

// int	var_exist(char *var, t_data *data)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(var);
// 	while (data->env[i])
// 	{
// 		if (!ft_strncmp(data->env[i], var, len) && data->env[i][len] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	var_exist(char *var, t_data *data)
{
	int	i;
	int	len;
	int	datalen;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		datalen = (int)ft_strlen(data->env[i]);
		if (!ft_strncmp(data->env[i], var, len)
			&& (data->env[i][len] == '=' || data->env[i][len] == '\0'))
		{
			if (data->env[i][len] == '\0' && datalen == len)
				return (1);
			if (data->env[i][len] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

void	add_to_env(char *var, t_data *data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(var);
	new_env[i] = NULL;
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	data->env = new_env;
}
