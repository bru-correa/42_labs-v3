#include "monitoring.h"

static int		check_dns_timeout(int data_file);
static char		**get_header_data(int data_file);
static char		*extract_response(char **header_data);
static double	get_dns_latency(int data_file);

char	*get_dns_response(t_request *request, int data_file)
{
	char	*response;
	char	**header_data;
	int		timeout;

	timeout = check_dns_timeout(data_file);
	if (timeout == TRUE)
	{
		response = ft_strdup("TIMEOUT");
		request->latency = 0;
		return (response);
	}
	header_data = get_header_data(data_file);
	response = extract_response(header_data);
	request->latency = get_dns_latency(data_file);
	return (response);
}

static double	get_dns_latency(int data_file)
{
	char	*line;
	double	latency;
	char	**line_data;

	line = ft_get_next_line(data_file);
	while (line != NULL && ft_strncmp(line, ";; Query time:", 14) != 0)
	{
		free(line);
		line = ft_get_next_line(data_file);
	}
	line_data = ft_split(line, ' ');
	free(line);
	latency = ft_atoi(line_data[3]);
	free_matrix(line_data);
	return (latency);
}

static int	check_dns_timeout(int data_file)
{
	char	*line;
	int		i;

	line = ft_get_next_line(data_file);
	for (i = 0; i < 4; i++)
	{
		free(line);
		line = ft_get_next_line(data_file);
	}
	if (ft_strncmp(line, ";; connection timed out;", 24) == 0)
	{
		free(line);
		return (TRUE);
	}
	free(line);
	return (FALSE);
}

static char	**get_header_data(int data_file)
{
	char	*line;
	char	**header_data;

	line = ft_get_next_line(data_file);
	while (line != NULL && ft_strncmp(line, ";; ->>HEADER", 12) != 0)
	{
		free(line);
		line = ft_get_next_line(data_file);
	}
	header_data = ft_split(line, ' ');
	free(line);
	return (header_data);
}

static char	*extract_response(char **header_data)
{
	char	*response;
	int		i;
	size_t	length;

	i = 0;
	while (header_data[i] != NULL
		&& strncmp(header_data[i], "status:", 8) != 0)
		i++;
	length = ft_strlen(header_data[i + 1]);
	header_data[i + 1][length - 1] = '\0';
	response = ft_strdup(header_data[i + 1]);
	free_matrix(header_data);
	return (response);
}
