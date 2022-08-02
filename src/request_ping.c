#include "monitoring.h"

static void	exec_ping(t_request *request, pid_t pid, int *pipe_fd);
static void	write_log(t_request *request, FILE *log_file, char *latency);
static void	write_log_timeout(t_request *request, FILE *log_file);

void	request_ping(t_request *request, FILE *log_file)
{
	int		timeout;
	char	*latency;
	pid_t	pid;
	int		pipe_fd[2];

	pipe_and_fork(pipe_fd, &pid);
	exec_ping(request, pid, pipe_fd);
	timeout = check_ping_timeout(pipe_fd[READ_END]);
	if (timeout == TRUE)
		write_log_timeout(request, log_file);
	else
	{
		latency = get_ping_latency(pipe_fd[READ_END]);
		write_log(request, log_file, latency);
	}
	close(pipe_fd[READ_END]);
}

// ! NULL output to STDOUT if it fail's, it will just print to STDERR (doc)
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

static void	write_log(t_request *request, FILE *log_file, char *latency)
{
	char	*time;

	time = get_time();
	fprintf(log_file, "%s|%s|PING|Url: %s|Latency %s|Status: HEALTHY\n",
		time, request->fields[NAME], request->fields[URL], latency);
	free(latency);
}

static void	write_log_timeout(t_request *request, FILE *log_file)
{
	char	*time;

	time = get_time();
	fprintf(log_file, "%s|%s|PING|Url: %s|Latency: TIMEOUT|Status: UNHEALTHY\n",
		time, request->fields[NAME], request->fields[URL]);
}
