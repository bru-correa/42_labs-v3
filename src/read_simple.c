#include "monitoring.h"

static void	print_log(char *line);
static void	print_head_log(char **log_data);
static void print_end_log(char **log_data, int latency_index, int status_index);

void	read_simple(int log_fd)
{
	char	*line;

	line = ft_get_next_line(log_fd);
	printf("%s\n", line);
	while (line != NULL)
	{
		print_log(line);
		free(line);
		line = ft_get_next_line(log_fd);
	}
}

static void	print_log(char *line)
{
	char	**log_data;

	log_data = ft_split(line, '|');
	print_head_log(log_data);
	if (ft_strncmp(log_data[LOG_PROTOCOL], "HTTP", 5) == 0)
		print_end_log(log_data, LOG_HTTP_LATENCY, LOG_HTTP_STATUS);
	else if (ft_strncmp(log_data[LOG_PROTOCOL], "DNS", 4) == 0)
		print_end_log(log_data, LOG_DNS_LATENCY, LOG_DNS_STATUS);
	else if (ft_strncmp(log_data[LOG_PROTOCOL], "PING", 5) == 0)
		print_end_log(log_data, LOG_PING_LATENCY, LOG_PING_STATUS);
	free_matrix(log_data);
}

static void	print_head_log(char **log_data)
{
	printf("----------------------------------------\n");
	print_in_blue("Name:");
	printf("%s\n", log_data[LOG_NAME]);
	print_in_blue("Address:");
	printf("%s\n", log_data[LOG_URL]);
	print_in_blue("Protocol:");
	printf("%s\n", log_data[LOG_PROTOCOL]);
	print_in_blue("Date:");
	printf("%s\n", log_data[LOG_DATE]);
}

static void print_end_log(char **log_data, int latency_index, int status_index)
{
	print_in_blue("Latency:");
	if (ft_strncmp(log_data[latency_index], "TIMEOUT", 8) == 0)
		print_in_red("TIMEOUT");
	else
		printf("%s\n", log_data[latency_index]);
	print_in_blue("Status:");
	if (ft_strncmp(log_data[status_index], "UNHEALTHY", 8) == 0 )
		print_in_red("UNHEALTHY");
	else
		print_in_green("HEALTHY");
}
