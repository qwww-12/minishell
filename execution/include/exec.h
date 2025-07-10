#ifndef EXEC_H
# define EXEC_H

# define ERR_FPIP "Problem init array pipefd\n"
# define ERR_FORK "Fork Failed\n"
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

#endif