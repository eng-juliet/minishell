/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:55:00 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/21 14:17:39 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

void	remove_env_var(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->len = ft_strlen(str);
	data->size = env_len(data->env);
	data->new_env = malloc(sizeof(char *) * (data->size + 1));
	if (!data->new_env)
		return ;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, data->len) == 0
			&& (data->env[i][data->len] == '='
			|| data->env[i][data->len] == '\0'))
			i++;
		else
			data->new_env[j++] = ft_strdup(data->env[i++]);
	}
	data->new_env[j] = NULL;
	i = 0;
	while (data->env[i])
		free(data->env[i++]);
	free(data->env);
	data->env = data->new_env;
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
