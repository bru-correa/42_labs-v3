#include "monitoring.h"

void	pipe_and_fork(int *pipe_fd, pid_t *pid)
{
	if (pipe(pipe_fd) < 0)
	{
		fprintf(stderr, "ERROR: Could not open pipe\n");
		exit(EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid < 0)
	{
		fprintf(stderr, "ERROR: Could not fork\n");
		exit(EXIT_FAILURE);
	}
}

void	redir_pipe_to_stdout(int *pipe_fd)
{
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[WRITE_END]);
	close(pipe_fd[READ_END]);
}
