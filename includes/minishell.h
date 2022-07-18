/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:11:00 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/25 22:20:18 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <term.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <curses.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "get_next_line.h"
# include "libft.h"
# include "color.h"
# define BUFFSIZE 100
# define TERM_TYPE_BUFF 2048
# define READ_END 0
# define WRITE_END 1
# define BUILTIN_FAIL 2
# define USAGE_ERROR 256
# define INVALID_IDENTIFER 257
# define NOT_NUM_ARG 258
# define NO_HOME_VAR 260
# define NO_OLDPWD_VAR 261
# define TOO_MANY_ARGS 262
# define ISDIR 263
# define BIN_ECHO 0
# define BIN_CD 1
# define BIN_PWD 2
# define BIN_EXPORT 3
# define BIN_UNSET 4
# define BIN_ENV 5
# define BIN_EXIT 6
# define BIN_NUM 7
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif
# define M_OK 0
# define M_ERR 1
# define HEREDOC_ERR 2
# define SIMPLE 0
# define PIPE 1
# define PIPE_FIRST 2
# define REDIRECT_IN 0
# define REDIRECT_HEREDOC 1
# define REDIRECT_OUT 2
# define REDIRECT_OUT_APPEND 3
# define DEFAULT_MODE 0
# define HEREDOC_MODE 1
# define EXEC_MODE_PARENT 2
# define EXEC_MODE_CHILD 3
//FOR TEST
volatile int	g_status;

typedef struct s_rdir
{
	int			heredock_quote;
	char		*fname;
	int			type;
	int			fd;
	char		*arg;
	void		*next;
}				t_rdir;

typedef struct s_node
{
	int			arg_count;
	int			need_to_free_str;
	int			need_to_free_arg;
	int			need_to_assign;
	char		*cmd;
	char		**arg;
	int			n_arg;
	int			n_rdir_arg;
	int			init_rdir;
	int			pid;
	void		*next;
	void		*prev;
	t_rdir		*rdir;
}				t_node;

typedef struct s_redirect
{
	int		type;
	int		arg1;
	char	*arg2;
	int		fd;
	char	*fname;
	int		expand;
}				t_redirect;

typedef struct s_pipe_line
{
	char				*cmd;
	char				**argv;
	t_redirect			**redirect_in;
	t_redirect			**redirect_out;
	int					pid;
	struct s_pipe_line	*next;
	struct s_pipe_line	*prev;
}				t_pipe_line;

typedef struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_std_backup
{
	int	stdin_backup;
	int	stdout_backup;
	int	stderr_backup;
}				t_std_backup;

typedef struct s_pipe_desc
{
	int	exec_type;
	int	fd_in;
	int	fd_out;
	int	fd_to_close;
}				t_pipe_desc;

struct			s_params;

typedef struct s_minishell
{
	t_env_list	*env_list;
	int			env_list_size;
	char		**env_arr;
	char		*history_file;
	int			exit_status;
	int			history_fd;
	int			(*built_in[BIN_NUM])(
			struct s_params *data,
			t_node *pipe_line);
}				t_minishell;

//--------------PARSER_DEFINE--------------//

typedef struct s_params
{
	int			key;
	char		*line;
	t_node		*node;
	t_node		*list;
	t_minishell	*minishell;
}				t_params;

typedef struct s_quotes
{
	int		i_arg;
	int		i;
	int		j;
	int		start;
	int		end;
	int		pass_quote;
	int		env_i;
	int		len_env;
	char	flag;
}			t_quotes;

//------------PARSER_DEFINE_END------------//

//init
int			init(t_params **data, char **envp);

//built-in
int			ft_pwd(t_params *data, t_node *pipe_line);
int			ft_cd(t_params *data, t_node *pipe_line);
int			ft_env(t_params *data, t_node *pipe_line);
int			ft_export(t_params *data, t_node *pipe_line);
int			ft_echo(t_params *data, t_node *pipe_line);
int			ft_unset(t_params *data, t_node *pipe_line);
int			ft_exit(t_params *data, t_node *pipe_line);

//env
int			env_copy(t_minishell *minishell, char **env);
char		*env_create_line(t_env_list *ptr);
int			env_fill_array(t_minishell *minishell);
int			env_to_array(t_minishell *minishell);
int			env_to_list(t_minishell *minishell, char **envp);
t_env_list	*new_env_elem(char *env_var);
int			env_set_key(t_env_list *elem, char *key);
int			env_set_val(t_env_list *elem, char *val);
void		env_list_clear(t_minishell *shell);
void		env_del_elem(t_env_list *env_list);
void		envlist_delone(t_minishell *minishell, char *key);
int			envlist_add_var(t_minishell *minishell, char **argv);
void		env_add_back(t_env_list **env_list, t_env_list *new_elem);
void		select_sort(t_env_list *ptr);
void		set_increment(int *arr);
int			envlist_change_val(t_env_list *env_list, char *key, char *new_val);
int			envarr_change_val(char **env, char *key, char *val);
int			envvar_validate(char *var);
int			envvar_validate_new(char *var);

//find_cmd
int			find_cmd(char *cmd, t_env_list *env_list, char **path_to_cmd);

//exec_command_line
void		get_correct_status(int exit_status);
int			start_exec_pipe(t_params *data);
int			exec_pipe_line(t_params *data);

//exec_cmd
int			exec_cmd(t_params *data, t_node *pipe_line,
				int fd_in, int fd_out);
int			exec_in_fork(t_params *data, t_node *pipe_line,
				t_pipe_desc *pipe_desc);

//pipe
t_pipe_desc	*pipe_desc_init(int exec_type, int fd_in, int fd_out,
				int fd_to_close);
int			pipe_exec(t_params *data, t_node *node, t_pipe_desc *pipe_desc);

//history
int			open_history_file(char *home_path);
void		ft_read_history(int fd);
int			put_history_line(char *line, int fd);

//utils
void		builtin_arr_init(t_minishell *minishell);
int			is_builtin(char *cmd);
int			ft_isspace(char c);
int			check_overflow(char *s);
void		free_str_arr(char **strings, int n_arg);
void		free_strarr_terminated(char **strings);
int			safe_close(int fd);
void		safe_free(void *data);
int			list_len(t_pipe_line *data);
int			env_len(t_env_list *ptr);

//err_handler
char		*ft_strerr(int error);
void		print_error(char *cmd, int error, char *arg);
char		*ft_getenv(t_env_list *env_list, char *name);
void		exit_minishell(t_params *data, int exit_status);

//signal
int			sighandler_set(int mode);

//heredoc
char		*heredoc(t_minishell *minishell, t_rdir *r_info, int index);

//heredoc_utils
char		*env_get_val(t_env_list *env_list, char *key);
char		*get_word(char *str);
int			expand_var(t_minishell *minishell, char *line, int fd, int *i);
int			heredoc_put_str(t_minishell *minishell, char *line,
				int fd, int expand);
char		*heredoc_fname(int index);

//redirect
int			make_redirect_s(t_minishell *minishell,
				t_rdir *redirect, int index);
int			cmd_redirect_s(t_rdir *redirect);
int			cmd_redirect_close(t_rdir *redirect);
int			pipeline_set_fd(t_minishell *minishell, t_node *pipe_line);
int			redirect_pipe(int fd_in, int fd_out);

//std_backup
int			stdbackup_copy(t_std_backup *std_backup);
int			stdbackup_set(t_std_backup *std_backup);
int			stdbackup_close(t_std_backup *std_backup);

//defenv_init
int			default_env(t_minishell *minishell);

//free_struct
void		free_minishell(t_minishell *minishell);
void		free_pipe_line(t_pipe_line *pipe_line);
void		redirect_clear(t_node *node);

//utils_exec
char		*get_last_argv(char *cmd, char **argv, int n_arg);
int			end_exec(t_params *data, t_std_backup *std_backup, int exit_status);
int			start_rdir(t_params *data, t_std_backup *std_backup);
void		change_underscore(t_params *data);

//cursed
char		**argv_crutch(char **argv, char *cmd, int n_arg);

//parser
int			somethind_ahead(char *line, int i);
int			is_it_specsym(char sym);
void		write_one_sym(t_params *data, t_quotes *quot, char *line);
int			next_quot_check(char *line, int i);
int			not_env(t_quotes *quot, t_params *data, char *line);
int			check_multi_dollars(char *line, t_quotes *quot,
				t_params *data, int counter);
int			get_new_len(char *line, t_quotes *quot, char *env_line);
int			is_dollar_ahead(char *line, int i);
int			get_finish(char *line, int i);
int			is_it_env(char **env, char *line, int end, int start);
int			get_env(t_params *data, t_quotes *quot, char *line, char **env);
int			check_command_before(char *line, int i);
int			get_len(char *bf_dollar, char *af_dollar, char *instead_of);
int			argument_count(t_params *data, t_quotes *quot, int count, int flag);
int			find_arguments(t_params *data, t_quotes *quot);
int			check_ahead(char *line, int i);
int			check_after_rdir(char *line, int i, char *type);
int			find_arguments(t_params *data, t_quotes *quot);
int			before_after(char *line, int i, int type);
int			fast_quotes_check(char *line);
int			parser(char *line, char **env, t_params *data);
int			heredock_behind(char *line, int i);
int			is_rdir(char sym);
int			is_it_letter(char sym);
int			even_or_odd(int dight);
int			is_nothing(char sym);
int			start_info(t_params *data, char *line, int *i, int *len);
int			check_len_of_command(char *line, int i);
int			we_need_this_quotes(char *line, int i, char flag);
int			dollar_in_double_quotes(t_quotes *quot, char *line);
int			start_command(t_quotes *quot, t_params *data,
				char *line, char **env);
int			pipe_bad_syntax(char *line);
int			rdir_bad_syntax(char *line);
void		check_flag(t_params *data, t_quotes *quot, char *line);
void		copy_env(t_quotes *quot, t_params *data, char *env_line);
void		env_join(t_params *data, t_quotes *quot, char *env_value);
void		get_new_memory(t_params *data, int len, t_quotes *quot);
void		data_node_init(t_params *data);
void		fill_argument(t_params *data, t_quotes *quot);
void		fill_command(t_params *data, t_quotes *quot);
void		find_command(t_params *data, t_quotes *quot);
void		check_dollar_with_single(t_params *data, int i);
void		check_quotes_utils(char *line, t_params *data, char **env);
void		param_init(t_quotes *tmp_quot);
void		before_inside(t_quotes *tmp_quot, t_params *data,
				char *line, char **env);
void		not_quotes(char *line, t_quotes *tmp_quot, t_params *data);
void		inside_quotes(char *line, t_quotes *tmp_quot,
				t_params *data, char **env);
void		work_with_dollar(t_quotes *quot, char *line,
				t_params *data, char **env);
void		work_with_dollar_outside(char *line, t_quotes *quot,
				t_params *data, char **env);
void		check_dollar(char *line, int i, int steps_next_quote, int count);
void		last_preparation(t_params *data, t_quotes *quot, int i, int flag);
void		add_rdir(t_rdir **rdir);
void		clear_list(t_node **list);
void		print_list(t_node *list);
void		print_node(t_node *node);
void		print_node2(t_node *node);
void		correct_count(t_params *data, int *i);
void		start_work_rdir(t_params *data, t_quotes *quot);
void		rewrite(t_params *data, int i);
void		check_dollar_with_quest(t_params *data);
void		rewrite_new_line(char *bf_dollar, int *i,
				char *instead_of, t_params *data);
void		rewrite_new_line_utils(char *af_dollar, int i, t_params *data);
void		find_new_command(t_quotes *quot, t_params *data,
				char *line, char **env);
char		*get_value(char *tmp_line, char **env);
t_node		*add_node(t_node **list, t_node *node);
t_node		*new_node(char *cmd, char **arg);
int			cycle(t_params *data, int res);
void		data_init(t_params *data);

#endif
