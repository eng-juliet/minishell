/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:51 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 19:28:04 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd_command(char **argv, t_data *data)
{
	const char	*target;
	char		*home;

	if (!argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			data->last_status = 1;
			return ;
		}
		target = home;
	}
	else
		target = argv[1];
	if (chdir(target) != 0)
	{
		perror("cd");
		data->last_status = 1;
		return ;
	}
	data->last_status = 0;
}

void	handle_pwd_command(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	handle_echo_command(char **argv, t_data *data)
{
	int	i;

	i = 1;
	data->newline = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		data->newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (data->newline)
		printf("\n");
	data->last_status = 0;
}

int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
