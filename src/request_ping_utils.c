#include "monitoring.h"

static int	check_ping_timeout(int data_file);

double	get_ping_latency(int data_file)
{
	char	*line;
	char	**line_data;
	double	latency;
	int		i;

	if (check_ping_timeout(data_file) == TRUE)
		return (0);
	line = ft_get_next_line(data_file);
	line_data = ft_split(line, ' ');
	free(line);
	i = 0;
	while (line_data[i] != NULL && ft_strncmp(line_data[i], "time=", 5) != 0)
		i++;
	latency = atof(&line_data[i][5]);
	free_matrix(line_data);
	return (latency);
}

static int	check_ping_timeout(int data_file)
{
	char	*line;

	line = ft_get_next_line(data_file);
	if (line == NULL)
		return (TRUE);
	free(line);
	return (FALSE);
}
