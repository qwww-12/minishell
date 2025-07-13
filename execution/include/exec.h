/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:00:48 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/13 17:41:27 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define ERR_FPIP "Problem init array pipefd\n"
# define ERR_FORK "Fork Failed\n"
# define ERR_DUP2 "Dup2 Failed\n"
# define ERR_DUP "Dup Failed\n"
# define ERR_CHDIR "Chdir Failed\n"
# define ERR_MANY_ARGS "minishell: exit: too many arguments\n"
# define READ 0
# define WRITE 1

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_red	t_red;

/*~~~~~~~~~~~~~~~~~~~~~~<core_exec.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	excute_commands(t_cmd *cmd, t_env **env);
/*~~~~~~~~~~~~~~~~~~~~~~<runtime.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	run_commands(t_cmd *cmd, t_env **env, int *back_up);
/*~~~~~~~~~~~~~~~~~~~~~~<child.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	start_child(t_cmd *cmd, t_env **env, int *back_up);
/*~~~~~~~~~~~~~~~~~~~~~~<heredooc.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	setup_heredocs(t_cmd *cmd, t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<leaks_fd.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	close_fd(int *fd);
void	close_all_fd(int *fd1, int *fd2);
/*~~~~~~~~~~~~~~~~~~~~~~<builtins.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	is_builtin(t_cmd *cmd);
void	start_builtin(t_cmd *cmd, t_env **env);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_echo.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_echo(t_cmd *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_env.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_env(t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_export.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_export(t_env *env, char **cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_unset.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_unset(t_env **env, char **cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_exit.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_exit(t_cmd *tmd, t_env *env, char **cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_cd.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_cd(t_env *env, char *pwd);
/*~~~~~~~~~~~~~~~~~~~~~~<t_envutils.c>~~~~~~~~~~~~~~~~~~~~~~*/
t_env	*list_new_node(char *value, char *key, bool eq);
char	**environment_to_array(t_env *env);
void	list_add_back(t_env **list, t_env *new);
int		list_size(t_env *list);
/*~~~~~~~~~~~~~~~~~~~~~~<path.c>~~~~~~~~~~~~~~~~~~~~~~*/
char	*find_path(t_env *env, char *cmd);
void	error_path_output(char *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<export_utils_0.c>~~~~~~~~~~~~~~~~~~~~~~*/
char	*get_valide_key(char *str);
void	swap_nodes(t_env *node1, t_env *node2);
void	desplay_list_export(t_env *env);
t_env	*ft_copy_env(t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<exit_utils_0.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	is_overflow(const char *str, size_t *ma);
/*~~~~~~~~~~~~~~~~~~~~~~<cd_utils_0.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	update_env_clean(t_env *env, char **newpwd, char **oldpwd);
bool	is_home(char *pwd);
/*~~~~~~~~~~~~~~~~~~~~~~<v_error.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	file_not_found(const char *file);
void	ambiguous_redirect_output(char *file);
/*~~~~~~~~~~~~~~~~~~~~~~<redirections.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	set_fd_redirections(t_cmd *cmd);
bool	dup2_fd_redirections(t_cmd *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<fd.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	store_io_fd(int *fds);
bool	restore_io_fd(int *fds);

#endif