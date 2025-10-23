/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:45:04 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 13:56:46 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset_command(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		data->last_status = 0;
		return ;
	}
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			printf("unset: %s: not a valid identifier\n", args[i]);
			data->last_status = 127;
		}
		else
		{
			remove_env_var(data, args[i]);
			data->last_status = 0;
		}
		i++;
	}
}

void	handle_env_command(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (args[1])
	{
		printf("env: too many arguments\n");
		data->last_status = 127;
		return ;
	}
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	data->last_status = 0;
}

int	calculate_exit_code(char *args)
{
	int	exit_code;

	exit_code = ft_atoi(args);
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	else
		exit_code = exit_code % 256;
	return (exit_code);
}

void	handle_exit_command(char **args, t_data *data)
{
	int	exit_code;

	printf("exit\n");
	close_all();
	if (!args[1])
	{
		ft_cleanup(data, data->line);
		exit(data->last_status);
	}
	if (!is_numeric(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		ft_cleanup(data, data->line);
		exit(255);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		data->last_status = 1;
		return ;
	}
	exit_code = calculate_exit_code(args[1]);
	ft_cleanup(data, data->line);
	exit(exit_code);
}
