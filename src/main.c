/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:51:50 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/28 19:21:36 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*get_input(t_data *data)
{
	char	*line;

	line = readline("$ ");
	if (!line)
	{
		printf("exit\n");
		free(line);
		free_env(data->env);
		data->env = NULL;
		exit(data->last_status);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

int	process_input(t_data *data)
{
	data->tokens = split_line_to_words(data->line);
	if (!data->tokens)
		return (1);
	expand(data->tokens, data);
	tokenize(data->tokens);
	if (is_syntax_error(data->tokens))
	{
		data->last_status = 2;
		free_tokens(data->tokens);
		return (1);
	}
	parse_tokens_to_command(data->tokens, data, &data->cmd);
	if (!data->cmd)
	{
		free_tokens(data->tokens);
		return (1);
	}
	return (0);
}

void	shell_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		g_last_sig = 0;
		data->line = get_input(data);
		if (g_last_sig == SIGINT)
		{
			data->last_status = 130;
			g_last_sig = 0;
		}
		if (process_input(data))
		{
			free(data->line);
			continue ;
		}
		g_last_sig = 0;  // Reset signal before command execution
		execute_pipeline(data);
		// Check if signal occurred during execution and no child process set the status
		if (g_last_sig == SIGINT)
		{
			data->last_status = 130;
			g_last_sig = 0;
		}
		free_tokens(data->tokens);
		free_command(data->cmd);
		free(data->line);
	}
	free_env(data->env);
	data->env = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	data.shell_name = argv[0];
	data.env = copy_env(envp);
	if (!data.env)
	{
		ft_putendl_fd("Error: Failed to copy environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data.last_status = 0;
	ft_minishell_print();
	setbuf(stdout, NULL);
	shell_loop(&data);
	ft_cleanup(&data, NULL);
	return (data.last_status);
}
