/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:00:48 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/10 19:57:59 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define ERR_FPIP "Problem init array pipefd\n"
# define ERR_FORK "Fork Failed\n"
# define ERR_DUP2 "Dup2 Failed\n"
# define ERR_DUP "Dup Failed\n"
# define READ 0
# define WRITE 0

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_red	t_red;

/*~~~~~~~~~~~~~~~~~~~~~~<core_exec.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	excute_commands(t_cmd *cmd, t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<core_exec.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	setup_heredocs(t_cmd *cmd, t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<leaks_fd.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	close_fd(int *fd);
/*~~~~~~~~~~~~~~~~~~~~~~<builtins.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	is_builtin(char *command);
void	start_builtin(t_cmd *cmd, t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_echo.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_echo(t_cmd *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<ft_env.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	ft_env(t_env *env);
/*~~~~~~~~~~~~~~~~~~~~~~<v_error.c>~~~~~~~~~~~~~~~~~~~~~~*/
void	file_not_found(const char *file);
/*~~~~~~~~~~~~~~~~~~~~~~<redirections.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	set_fd_redirections(t_cmd *cmd);
bool	dup2_fd_redirections(t_cmd *cmd);
/*~~~~~~~~~~~~~~~~~~~~~~<fd.c>~~~~~~~~~~~~~~~~~~~~~~*/
bool	store_io_fd(int *fds);
bool	restore_io_fd(int *fds);
#endif