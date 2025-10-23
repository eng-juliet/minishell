/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:55:17 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/28 20:06:38 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_last_sig;

// ==============================
// ENUMS
// ==============================

typedef enum e_token_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	UNKNOWN
}						t_token_type;

// ==============================
// STRUCTS
// ==============================

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				**argv;
	char				**path;
	char				*full_path;
	char				*next_cmd;
	int					i;
	int					infile;
	int					outfile;
	int					builtin_fun;
	int					pipe_fd[2];
	int					prev_pipe;
	pid_t				pid;
	int					rdir_flag;
	t_token				*redirections;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				**env;
	char				*shell_name;
	char				*slash;
	char				*line;
	char				**new_env;
	int					last_status;
	int					newline;
	int					len;
	int					size;
	t_command			*cmd;
	t_token				*tokens;
}						t_data;

// ==============================
// Main.c
// ==============================

void					shell_loop(t_data *data);
char					*get_input(t_data *data);
char					**copy_env(char **envp);

// ==============================
// TOKENIZATION / PARSING
// ==============================

t_token					*split_line_to_words(char *line);

int						ft_isspace(char s);
int						handle_quotes(const char *line, int i, char quote,
							int *new_pos);
int						is_special_char(char c);
int						count_tokens(const char *line);
int						token_length(const char *line, int *i);
t_token					*create_token_node(const char *line, int i, int len);
void					create_token(t_token **token, char *value,
							t_token_type type);
void					tokenize(t_token *tokens);
void					mark_commands(t_token *tokens);
int						is_syntax_error(t_token *tokens);
void					free_tokens(t_token *token);

// ==============================
// EXPANSION
// ==============================

void					expand(t_token *tokens, t_data *data);
char					*expand_token_value(char *input, t_data *data);
char					*handle_single_quote(char *input, int *i);
char					*handle_double_quote(char *input, int *i, t_data *data);
char					*handle_dollar(char *input, int *i, t_data *data);
char					*join_and_free(char *a, char *b);
int						is_quoted(char *str);
void					free_words(char **words);
int						count_words(char *str);
char					*get_word(char *str, int *i);
char					*handle_double_quote_inner(char *input, int *i,
							t_data *data, char *res);
void					insert_split_tokens(t_token *cur, t_token *next,
							char **words);
char					**split_on_whitespace(char *str);
int						contains_unquoted_variable(char *input);

// ==============================
// BUILTIN EXECUTION
// ==============================

int						is_builtin(char *command);
void					run_builtin(char **argv, t_data *data);
int						valid_identifier(char *str);
void					free_env(char **env);
void					handle_echo_command(char **argv, t_data *data);
void					handle_cd_command(char **argv, t_data *data);
void					handle_pwd_command(void);
void					handle_export_command(char **args, t_data *data);
void					handle_unset_command(char **argv, t_data *data);
void					handle_env_command(char **args, t_data *data);
void					handle_exit_command(char **argv, t_data *data);

// ==============================
// UTILITY FUNCTIONS
// ==============================

void					print_exported_env(char **env);
int						var_exist(char *var, t_data *data);
void					add_to_env(char *var, t_data *data);
int						env_len(char **env);
void					remove_env_var(t_data *data, char *str);
int						is_numeric(const char *str);
void					init_cmd(t_command **cmd);
void					add_list_back(t_command **head, t_command *tmp);
int						process_input(t_data *data);
void					link_token(t_token **head, t_token **current,
							t_token *new_token);
int						handle_special_char(char *line, int *i, int *total_len);
int						handle_regular_token(char *line, int *i,
							int *total_len);
int						handle_output_redirection(t_token *token,
							t_command *cmd);
int						handle_input_redirection(t_token *token,
							t_command *cmd);
int						handle_append_redirection(t_token *token,
							t_command *cmd);
int						handle_heredoc_token(t_token *token, t_command *cmd,
							t_data *data);
void					init_loop(t_command **cmd, t_token **cur,
							t_token *tokens);

// ==============================
// SIGNALS
// ==============================

void					set_signals_interactive(void);
void					set_signals_parent(void);
void					set_signals_child(void);
void					set_signals_heredoc_child(void);
void					set_signals_after_child(void);
void					after_child(int signo);
t_token					*split_line_to_words(char *line);
void					free_tokens(t_token *head);
void					execute_redirection(t_command *cmd);
void					parse_tokens_to_command(t_token *tokens, t_data *data,
							t_command **cmd);
void					free_command(t_command *cmd);

// ==============================
// PIPE EXECUTION
// ==============================
int						handle_heredoc(char *str, t_data *data);
void					ft_initialize_pipe(t_command *cmd);
int						ft_error(t_command *cmd, t_data *data, int flag);
void					ft_pipe_execute(t_command *cmd, t_data *data);
void					parent(t_command *cmd);
void					free_pipeline(t_command *cmd);
void					execute_pipeline(t_data *data);
void					ft_pipe_execute(t_command *cmd, t_data *data);
void					continue_pipe_execute(t_command *cmd, t_data *data);
void					get_cmd(t_command *cmd, t_data *data);
int						has_heredoc(t_token *token);
void					wait_for_children(t_data *data, t_command *last_cmd);
void					find_path(t_command *cmd, t_data *data);

// ==============================
// CLEANUP FUNCTIONS
// ==============================

void					free_data(t_data *data);
void					free_argv(char **argv);
void					ft_fds(t_command *cmd);
void					ft_cleanup(t_data *data, char *line);
void					close_all(void);
#endif
