/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:51:37 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/23 18:14:30 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(t_command *cmd, int flag)
{
	if (flag == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		if (cmd && cmd->argv && cmd->argv[0])
			ft_putendl_fd(cmd->argv[0], 2);
		else
			ft_putendl_fd("(unknown)", 2);
	}
	else if (flag == 126)
	{
		ft_putstr_fd("permission denied: ", 2);
		if (cmd && cmd->argv && cmd->argv[0])
			ft_putendl_fd(cmd->argv[0], 2);
		else
			ft_putendl_fd("(unknown)", 2);
	}
	else if (flag == 128)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		if (cmd && cmd->argv && cmd->argv[0])
			ft_putendl_fd(cmd->argv[0], 2);
		else
			ft_putendl_fd("(unknown)", 2);
	}
}

int	ft_error(t_command *cmd, t_data *data, int flag)
{
	print_error_message(cmd, flag);
	if (flag == 1)
		perror("minishell");
	if (flag != 127 && flag != 126 && flag != 128)
		perror("Error"); //edit it
	ft_cleanup(data, NULL);
	if (flag != 127 && flag != 126 && flag != 128)
		exit(EXIT_FAILURE);
	exit(flag);
}
