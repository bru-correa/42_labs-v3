#include "monitoring.h"

static void	exec_dns_lookup(t_request *request, pid_t pid, int *pipe_fd);
static void	write_log_timeout(t_request *request, FILE *log_file,
	int data_file);
static void	write_log(t_request *request, FILE *log_file, int data_file);

void	lookup_dns(t_request *request, FILE *log_file)
{
	int		timeout;
	pid_t	pid;
	int		pipe_fd[2];

	pipe_and_fork(pipe_fd, &pid);
	exec_dns_lookup(request, pid, pipe_fd);
	timeout = check_dns_timeout(pipe_fd[READ_END]);
	if (timeout == TRUE)
		write_log_timeout(request, log_file, pipe_fd[READ_END]);
	else
		write_log(request, log_file, pipe_fd[READ_END]);
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

static void	write_log_timeout(t_request *request, FILE *log_file, int data_file)
{
	char	*time;

	time = get_time();
	fprintf(log_file, "%s|%s|DNS|Url: %s|DNS_Server: %s|Response: TIMEOUT|",
		time, request->fields[NAME], request->fields[URL],
		request->fields[DNS_SERVER]);
	fprintf(log_file, "Latency: TIMEOUT|Status: UNHEALTHY\n");
	close(data_file);
}

// ! Always get the latency after the response(DOC)
static void write_log(t_request *request, FILE *log_file, int data_file)
{
	char	*time;
	char	*response;
	int		latency;

	time = get_time();
	response = get_dns_response(data_file);
	latency = get_dns_latency(data_file);
	fprintf(log_file, "%s|%s|DNS|Url: %s|DNS_Server: %s|Response: %s|",
		time, request->fields[NAME], request->fields[URL],
		request->fields[DNS_SERVER], response);
	fprintf(log_file, "Latency: %d ms|Status: ", latency);
	if (ft_strncmp(response, "NOERROR", 8) == 0)
		fprintf(log_file, "HEALTHY\n");
	else
		fprintf(log_file, "UNHEALTHY\n");
	free(response);
	close(data_file);
}
