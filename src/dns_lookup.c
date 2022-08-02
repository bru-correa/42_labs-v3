#include "monitoring.h"

static void	exec_dns_lookup(t_request *request, pid_t pid, int *pipe_fd);
static void	write_dns_log(t_request *request, FILE *log_file, int data_file);

void	lookup_dns(t_request *request, FILE *log_file)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe_and_fork(pipe_fd, &pid);
	exec_dns_lookup(request, pid, pipe_fd);
	write_dns_log(request, log_file, pipe_fd[READ_END]);
	close(pipe_fd[READ_END]);
}

static void	exec_dns_lookup(t_request *request, pid_t pid, int *pipe_fd)
{
	char	*dns_server_arg;

	if (pid == CHILD_ID)
	{
		redir_pipe_to_stdout(pipe_fd);
		dns_server_arg = ft_strjoin("@", request->fields[DNS_SERVER]);
		execlp("dig", "dig", dns_server_arg, request->fields[URL],
			"+timeout=2", NULL);
	}
	else if (pid > CHILD_ID)
	{
		close(pipe_fd[WRITE_END]);
		waitpid(pid, NULL, WNOHANG);
	}
}

// TODO Maybe write a function with a common log start for every protocol
static void	write_dns_log(t_request *request, FILE *log_file, int data_file)
{
	char	*time;
	char	*response;

	time = get_time();
	response = get_dns_response(request, data_file);
	fprintf(log_file, "%s|%s|DNS|Url: %s|DNS_Server: %s|Response: %s|",
		time, request->fields[NAME], request->fields[URL],
		request->fields[DNS_SERVER], response);
	fprintf(log_file, "Latency: ");
	if (request->latency == 0)
		fprintf(log_file, "TIMEOUT|");
	else
		fprintf(log_file, "%.1f|", request->latency);
	if (ft_strncmp(response, "NOERROR", 8) == 0)
	{
		fprintf(log_file, "HEALTHY\n");
		print_simple_dns(request, time, TRUE);
	}
	else
	{
		fprintf(log_file, "UNHEALTHY\n");
		print_simple_dns(request, time, FALSE);
	}
	free(response);
}
