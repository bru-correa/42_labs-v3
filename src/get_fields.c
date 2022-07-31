#include "monitoring.h"

static void	del_newline(char **protocol);

char	**get_next_fields(int database_fd)
{
	char	*line;
	char	**fields;

	line = ft_get_next_line(database_fd);
	fields = ft_split(line, '\t');
	free(line);
	if (fields == NULL)
		return (NULL);
	del_newline(fields);
	return (fields);
}

static void	del_newline(char **fields)
{
	int		field_len;
	int		fields_index;

	fields_index = 0;
	while (fields[fields_index + 1]!= NULL)
		fields_index++;
	field_len = ft_strlen(fields[fields_index]);
	fields[fields_index][field_len - 1] = '\0';
}
