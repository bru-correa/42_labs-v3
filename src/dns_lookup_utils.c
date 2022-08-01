#include "monitoring.h"

static char	**get_header_data(int data_file);
static char	*extract_response(char **header_data);

char	*get_dns_response(int data_file)
{
	char	*response;
	char	**header_data;

	header_data = get_header_data(data_file);
	response = extract_response(header_data);
	return (response);
}

int	get_dns_latency(int data_file)
{
	char	*line;
	int		latency;
	char	**data_chunks;

	line = ft_get_next_line(data_file);
	while (line != NULL && ft_strncmp(line, ";; Query time:", 14) != 0)
	{
		free(line);
		line = ft_get_next_line(data_file);
	}
	data_chunks = ft_split(line, ' ');
	free(line);
	latency = ft_atoi(data_chunks[3]);
	free_matrix(data_chunks);
	return (latency);
}

int	check_dns_timeout(int data_file)
{
	char	*line;
	int		i;

	line = ft_get_next_line(data_file);
	for (i = 0; i < 4; i++)
	{
		free(line);
		line = ft_get_next_line(data_file);
	}
	if (ft_strncmp(line, ";; connection timeout;", 22) == 0)
		return (TRUE);
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
