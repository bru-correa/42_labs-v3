#include "monitoring.h"

static void	exec_ping(t_request *request, pid_t pid, int *pipe_fd);
static void	write_ping_log(t_request *request, FILE *log_file, int data_file);

void	request_ping(t_request *request, FILE *log_file)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe_and_fork(pipe_fd, &pid);
	exec_ping(request, pid, pipe_fd);
	write_ping_log(request, log_file, pipe_fd[READ_END]);
	close(pipe_fd[READ_END]);
}

static void	exec_ping(t_request *request, pid_t pid, int *pipe_fd)
{
	if (pid == CHILD_ID)
	{
		redir_pipe_to_stdout(pipe_fd);
		close(STDERR_FILENO);
		execlp("ping", "ping", request->fields[URL], "-c1", NULL);
	}
	else if (pid > CHILD_ID)
	{
		close(pipe_fd[WRITE_END]);
		waitpid(pid, NULL, WNOHANG);
	}
}

static void	write_ping_log(t_request *request, FILE *log_file, int data_file)
{
	char	*time;

	time = get_time();
	write_log_head(request, log_file, time);
	request->latency = get_ping_latency(data_file);
	if (request->latency == 0)
	{
		fprintf(log_file, "TIMEOUT|");
		fprintf(log_file, "UNHEALTHY\n");
		print_simple(request, time, FALSE);
	}
	else
	{
		fprintf(log_file, "%.1f ms|", request->latency);
		fprintf(log_file, "HEALTHY\n");
		print_simple(request, time, TRUE);
	}
	fflush(log_file);
}
