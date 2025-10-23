/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:47:55 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 15:54:23 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

void	run_builtin(char **argv, t_data *data)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strcmp(argv[0], "cd") == 0)
		handle_cd_command(argv, data);
	else if (ft_strcmp(argv[0], "export") == 0)
		handle_export_command(argv, data);
	else if (ft_strcmp(argv[0], "unset") == 0)
		handle_unset_command(argv, data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		handle_exit_command(argv, data);
	else if (ft_strcmp(argv[0], "echo") == 0)
		handle_echo_command(argv, data);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		handle_pwd_command();
	else if (ft_strcmp(argv[0], "env") == 0)
		handle_env_command(argv, data);
}
