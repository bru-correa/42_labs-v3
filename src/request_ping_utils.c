#include "monitoring.h"

int	check_ping_timeout(int data_file)
{
	char	*line;

	line = ft_get_next_line(data_file);
	if (line == NULL)
		return (TRUE);
	free(line);
	return (FALSE);
}

char	*get_ping_latency(int data_file)
{
	char	*line;
	char	*latency;
	char	**line_data;
	int		i;

	line = ft_get_next_line(data_file);
	line_data = ft_split(line, ' ');
	free(line);
	i = 0;
	while (line_data[i] != NULL && ft_strncmp(line_data[i], "time=", 5) != 0)
		i++;
	latency = ft_strdup(&line_data[i][5]);
	free_matrix(line_data);
	return (latency);
}
