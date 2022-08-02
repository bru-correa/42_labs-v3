#include "monitoring.h"

static void	update_requests(t_request *first_request, FILE *log_file);
static void	call_request(t_request *request, FILE *log_file);

void	start_monitoring(t_request *first_request, FILE *log_file)
{
	struct timeval	start_time;
	struct timeval	end_time;
	int				time_spent;

	while (1)
	{
		gettimeofday(&start_time, NULL);
		update_requests(first_request, log_file);
		gettimeofday(&end_time, NULL);
		time_spent = end_time.tv_sec - start_time.tv_sec;
		sleep(60 - time_spent);
	}
}

static void	update_requests(t_request *first_request, FILE *log_file)
{
	t_request	*request;

	request = first_request;
	while (request != NULL)
	{
		request->interval_counter--;
		if (request->interval_counter <= 0)
			call_request(request, log_file);
		request = request->next;
	}
}

static void	call_request(t_request *request, FILE *log_file)
{
	if (ft_strncmp(request->fields[PROTOCOL], "HTTP", 5) == 0)
	{
		request_http(request, log_file);
		request->interval_counter = ft_atoi(request->fields[HTTP_INTERVAL]);
	}
	else if (ft_strncmp(request->fields[PROTOCOL], "DNS", 4) == 0)
	{
		lookup_dns(request, log_file);
		request->interval_counter = ft_atoi(request->fields[DNS_INTERVAL]);
	}
	else if (ft_strncmp(request->fields[PROTOCOL], "PING", 5) == 0)
	{
		request_ping(request, log_file);
		request->interval_counter = ft_atoi(request->fields[PING_INTERVAL]);
	}
}
