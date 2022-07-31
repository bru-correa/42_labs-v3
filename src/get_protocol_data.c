#include "monitoring.h"

static void	del_newline(char **protocol);

char	**get_next_protocol_data(int database_fd)
{
	char	*line;
	char	**protocol;

	line = ft_get_next_line(database_fd);
	protocol = ft_split(line, '\t');
	free(line);
	if (protocol == NULL)
		return (NULL);
	del_newline(protocol);
	return (protocol);
}

static void	del_newline(char **protocol)
{
	int		last_data_len;
	int		data_index;

	data_index = 0;
	while (protocol[data_index + 1]!= NULL)
		data_index++;
	last_data_len = ft_strlen(protocol[data_index]);
	protocol[data_index][last_data_len - 1] = '\0';
}
