/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:38:00 by artheon           #+#    #+#             */
/*   Updated: 2024/12/06 13:02:47 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <dirent.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include <errno.h> 
# include <stdbool.h>
# include <sys/wait.h>

# define SUCCESS 0
# define ERROR_MALLOC 3

# define PATH_MAX 4096

extern int	g_signal;

typedef struct s_quote_state
{
	size_t	in_single;
	size_t	in_double;
	size_t	i;
	char	c;
}	t_quote_state;

typedef struct s_parse_context
{
	int		status;
	char	**env;
	char	*result;
	int		*k;
	int		*i;
}	t_parse_context;

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_command
{
	char				**args;
	int					token_count;
	t_token				*tokens;
	int					infile;
	int					outfile;
	int					status;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

enum					e_tree_type
{
	EXEC_LIST = 0,
	OPPERATOR_AND,
	OPPERATOR_OR,
};

typedef struct s_expand
{
	int					act;
	struct s_expand		*prev;
	struct s_expand		*next;
}						t_expand;

typedef struct s_free_heredoc
{
	char	**env_ptr;
	char	**split_token_ptr;
	char	*token_ptr;
}						t_free_heredoc;

typedef struct s_process_id
{
	int					*tab_pid;
	int					index;
}						t_tab_pid;

enum					e_bool
{
	FALSE = 0,
	TRUE
};

char		*trim_whitespace(char *str);
char		*expand_variable(char *line, int status, char **env);
size_t		count_token(char *line);
size_t		calculate_token_size(char *line, int status, char **env);
char		**parse_token(char *line, int status, char **env);
int			handle_quotes(char *line, size_t *i);
char		*allocate_token(char *line, int *i, int status, char **env);
void		handle_single_quote(char *line, int *i, char *result, int *k);
void		handle_double_quote(char *line, t_parse_context *ctx);
char		*expand_and_return(char *line, int *i, int status, char **env);
void		extract_token(char *line, t_parse_context *ctx);
t_command	*new_command_node(char **args, char **envp, int status);
t_command	*parse_command_line(char *line, int status, char **env);
void		add_command_node(t_command **head, t_command *new_node);
char		*ft_strtok(char *str, const char *delim);
void		setup_pipes(t_command *cmd_list);
int			check_redirections(t_command *cmd, char **args, char **env, \
				char **tokenSplit);
char		*handle_here_doc(char *limiter, t_command *cmd, \
				t_free_heredoc *free_hd);
int			handle_here_doc_redirection(t_command *cmd, char *limiter, \
				t_free_heredoc *free_hd);
int			handle_filin_redirection(t_command *cmd, char *filename);
int			handle_filout_redirection(t_command *cmd, char *filename, \
				int append);
void		free_command_list(t_command *cmd_list);
void		free_command(t_command *cmd);
void		free_split(char **split);
int			check_syntax_errors(char *line, int *status);
int			check_redirection_errors(char *line, int *status);
size_t		handle_special_characters(char *line, size_t i);
size_t		handle_regular_token(char *line, int *i, int status, char **env);
size_t		handle_redirection_token(char *line, int *i);
size_t		handle_variable_expansion(char *line, int *i, int status, \
				char **env);
size_t		handle_double_quote_token(char *line, int *i, int status, \
				char **env);
size_t		handle_single_quote_token(char *line, int *i);
t_token		*tokenize_arguments(char **args, int *token_count, char **envp);
void		free_tokens(t_token *tokens, int token_count);
void		setup_signal_handlers(void);
void		setup_signal_handlers_heredoc(void);
int			is_command(const char *arg, char **envp);
char		**line_split(char *line, char c);
void		toggle_quotes(char c, t_quote_state *state);
size_t		skip_to_next_pipe(char *line, t_quote_state *state);
size_t		get_pipe_length(char *line, t_quote_state *state);
char		*copy_pipe_cmd(char *line, size_t *i, size_t length);
int			check_double_pipe_error(char *line, int *status, \
				t_quote_state state);
int			check_single_pipe_error(char *line, int *status, \
				t_quote_state state);
int			allocate_handle_redirection(char *line, char *result, int *i, \
				int *k);
void		process_line(char *line, t_parse_context *ctx);
char		*check_var_valid(char *line);

// # ====================================================== #
// |														|
// |						utils							|
// |														|
// # ====================================================== #

//free_1.c
void		free_tab_tab(char **tab);
void		ft_print_error_malloc(void);

//ft_join_utils.c
char		*ft_strjoin_equal_val(char *s1, char *s2);
char		*ft_strjoin_path_without_free(char *s1, char *s2);
char		*ft_strjoin_wihtout_free(char *s1, char *s2);
char		*ft_strjoin_path(char *s1, char *s2);

//ft_utils_1.c
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *str);
int			ft_strcmp_lib(const char *str1, const char *str2);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_occ(char *str, char c);
int			ft_strchr(char *str, char *find);

//ft_utils_2.c
int			ft_size_malloc_long_long(long long nb);
char		*ft_itoa_long_long(long long nb);
char		*ft_str_cat_long_long(char *new_str, long long status);

//ft_utils_3.c
int			ft_isalphanum(int c);
int			ft_strcmp(char *str1, char *str2);
char		*ft_strdup(char *str);

//ft_utils_4.c
int			ft_strlen_2d(char **str);

//ft_utils_5.c
int			count_world(char const *s, char sep);
char		*dup_word(char const *s, int start, int end);
char		**ft_split(char *s, char c);
int			ft_len_tab_tab(char **env);

//ft_utils_6.c
int			ft_is_ascii(char c);
int			ft_count_itoa(int n);
char		*ft_itoa(int n);
char		*ft_strjoin_1_malloc(char *str1, char *str2);

//ft_utils_7.c
char		*ft_join_char(char *str, char c);
char		*ft_strjoin(char *str1, char *str2);
char		*ft_strjoin_1_malloc_expand(char *str1, char *str2);
void		ft_end_1(int size, int *exit_status);

//ft_utils_debug.c
void		print_tab_tab(char **tab);

// ft_linked_list.c
int			ft_linked_list_size(t_command *lst);

// # ====================================================== #
// |														|
// |					EXPORT								|
// |														|
// # ====================================================== #

void		print_tab_tab(char **tab);
void		clean_env_value(char ***new_env);
void		ft_print_env_ascii_order(char **env);
void		print_tab_tab_ascii_order(char **tab);
void		ft_add_export_value(char **export, char *str);
int			ft_strlen(char *str);
int			ft_find_back_s(char *str);
int			ft_len_tab_tab(char **env);
int			equal_or_nothing(char *str);
int			check_after_equal(char *export);
int			value_start_equal(char *export);
int			ft_check_export_name(char *str);
int			ft_check_empty_export(char *export);
int			ft_strcmp_ascii_order(char *s1, char *s2);
int			ft_is_export_in_env(char **env, char *str);
int			ft_find_export_index(char **env, char *str);
int			ft_export_name(char *str, char **export_name);
int			ft_realloc_env(char ***env, int size);
char		*add_null(char *export);
char		*ft_find_export_name(char *str);
char		*export_and_equal(char *export);
char		*export_and_empty(char *export);
char		*add_quote_to_value(char *export);
char		*add_equal_null_char(char *export);
char		*ft_str_dup_env(char *s1, char *s2);
char		*assign_export_empty_value(char *export);
char		*ft_change_shlvl_export(char *shlvl);
char		**dup_env(char **env);
char		**dup_env_ascii_order(char **env);
int			ft_get_path_in_env(char **envp, char ***env, int *i);
void		ft_check_missing_env_2(char **env_val, char ***env,
				int *i);
void		ft_check_missing_env(char ***env, int *i);
char		*ft_get_export_value(char *str);
int			ft_check_if_i_print_env_i(char *str);
void		ft_change_export(char ***env, char *str);
int			ft_do_the_export(char ***env, char *export_str);
int			ft_export(char ***env, char **arg, int free);

// # ====================================================== #
// |														|
// |					UNSET								|
// |														|
// # ====================================================== #

int			ft_unset_is_in_env(char **env, char *unset_str);
int			ft_find_unset_index(char **env, char *unset_str);
int			ft_copy_env_exept_unset(char **env, int unset_index);
int			ft_unset(char ***env, char **cmd);

// # ====================================================== #
// |														|
// |						CD								|
// |														|
// # ====================================================== #
void		ft_change_pwd_old_pwd2(char ***env, char *current_path);
void		ft_change_pwd_old_pwd(char *current_path,
				char *new_path,
				char ***env);
int			is_export_name_in_env(char **env, char *str);
int			ft_cdpath(char **pathtab, char **env);
int			ft_msg_err_chdir(char *str);
void		ft_msg_err_getcwd(void);
int			ft_get_env_value2(char **env_name, char *env, char *str,
				char **env_value);
char		*ft_get_env_value(char **env, char *str);
int			ft_cd_parsing(char **path_tab);
int			ft_cd_home(char ***env);
int			ft_cd_dash(char ***env);
int			ft_cd_cdpath(char **path_tab, char ***env);
int			ft_cd(char **path_tab, char ***env);

// # ====================================================== #
// |														|
// |					ECHO								|
// |														|
// # ====================================================== #

int			ft_check_echo_param_only_one(char *str);
void		ft_check_echo_param(char **tab, int *j, int *param);
int			ft_echo2(char **tab, int i, int param);
int			ft_echo_2_1(char **tab, int *i);
int			ft_echo(char **tab);

// # ====================================================== #
// |														|
// |						PWD								|
// |														|
// # ====================================================== #

char		*ft_get_builtin_err_msg(char *builtin);
int			ft_pustr_builtin_pwd(char *str);
int			ft_pwd(char **tab, char **env);

// # ====================================================== #
// |														|
// |					EXIT								|
// |														|
// # ====================================================== #

enum e_bool	ft_atoi(char *str, long long int *res);
int			ft_check_exit_char(char *str);
void		ft_exit_parsing(char **arg,
				long long int *exit_value, int *exit_flag);
int			ft_exit(char **arg, int *exit_flag);

// # ====================================================== #
// |														|
// |						ENV								|
// |														|
// # ====================================================== #

int			ft_pustr_builtin_env(char *str);
int			ft_env(char **env);

// # ====================================================== #
// |														|
// |						EXEC							|
// |														|
// # ====================================================== #

bool		ft_is_builtin(char **cmd);
int			check_absolute_path_builtin(char **arg);
int			ft_exec_builtin(char **arg, char ***env, int *exit_flag,
				t_command *tree);
int			ft_exec_cmd_fork(t_command *tree, char ***env, t_tab_pid pid);
int			ft_exec(t_command *tree, char ***env, int *status);
int			ft_find_builtin(char *cmd, char **cmd_tab, char ***env, \
				int *exit_flag);
char		*ft_itoa_shlvl(int nb);
char		**ft_copy_env(char **envp);
char		*ft_change_shlvl(char **envp, char *shlvl);
int			ft_check_shlvl_export(char ***env, char *export_str);
void		ft_replace_last_command(char ***env, char **str);
char		*ft_get_path(void);
void		ft_close(int fd);
void		close_fd_list(t_command *cmd_list);

// # ====================================================== #
// |														|
// |				CHOOSE AND CHECK CMD					|
// |														|
// # ====================================================== #

char		**ft_get_path_cmd(char **env);
int			ft_check_cmd(char *cmd);
void		free_exit(char **env, char **cmd);
void		free_check_path(char ***env, char **msg_err, char ***path_split);
void		ft_check_path_execve(char **path, \
				char ***cmd, char ***env, t_command *cmd_list);
void		find_cmd_4(char **cmd, char ***env, t_command *cmd_list);
void		find_cmd_5(char ***env, char **cmd, t_command *cmd_list);
void		ft_check_path_cmd_2(char **path_split, char ***env, \
				t_command *cmd_list);
int			ft_check_path_cmd(char ***env, char ***cmd, t_command *cmd_list);
int			find_cmd_2(char **cmd, int *status, char ***env, \
				t_command *cmd_list);
void		find_cmd_3(char ***env, char **cmd, t_command *cmd_list);
int			find_cmd(char ***env, char ***cmd, t_command *cmd_list);
int			ft_getout(t_command *cmd_list, char **msg_err, char ***env, \
				char ***path_split);

// # ====================================================== #
// |														|
// |						ERROR							|
// |														|
// # ====================================================== #

void		ft_msg_err_getcwd(void);
int			ft_msg_err_chdir(char *str);
void		print_command_list(t_command *cmd_list);

#endif
