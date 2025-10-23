/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:04:29 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/28 20:07:03 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_heredoc_loop(char *str, char *line, int p[2])
{
	close(p[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDERR_FILENO, "-bash: warning: here-document ", 31);
			write(STDERR_FILENO, "delimited by end-of-file (wanted '", 34);
			write(STDERR_FILENO, str, ft_strlen(str));
			write(STDERR_FILENO, "')\n", 3);
			close(p[1]);
			break ;
		}
		if (ft_strcmp(line, str) == 0)
		{
			free(line);
			break ;
		}
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
	}
	close(p[1]);
}

int	continue_heredoc(pid_t pid, int p[2], t_data *data)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		close(p[0]);
		return (-1);
	}
	set_signals_interactive();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->last_status = 130;
		close(p[0]);
		return (-1);
	}
	return (0);
}

void	close_all(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

int	handle_heredoc(char *str, t_data *data)
{
	int		p[2];
	pid_t	pid;

	if (pipe(p) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(p[0]);
		close(p[1]);
		return (-1);
	}
	if (pid == 0)
	{
		start_heredoc_loop(str, NULL, p);
		close_all();
		ft_cleanup(data, NULL);
		exit(0);
	}
	set_signals_parent();
	close(p[1]);
	if (continue_heredoc(pid, p, data) == -1)
		return (-1);
	return (p[0]);
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}
