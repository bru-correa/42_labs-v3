#include "monitoring.h"

static t_request	*create_request(char **fields);
static void			push_request(t_request *first, t_request *new);
static int			open_database_file(char *filename);

// ? Maybe extract this function
t_request	*get_requests(char *database_filename)
{
	char		**fields;
	t_request	*first_request;
	t_request	*new_request;
	int			database_fd;

	database_fd = open_database_file(database_filename);
	fields = get_next_fields(database_fd);
	if (fields == NULL)
	{
		fprintf(stderr, "ERROR: Empty database\n");
		close(database_fd);
		exit(EXIT_FAILURE);
	}
	first_request = create_request(fields);
	fields = get_next_fields(database_fd);
	while (fields != NULL)
	{
		new_request = create_request(fields);
		push_request(first_request, new_request);
		fields = get_next_fields(database_fd);
	}
	close(database_fd);
	return (first_request);
}

// TODO Maybe create the interval counter here (need to analyze protocol)
static t_request	*create_request(char **fields)
{
	t_request	*request;

	request = malloc(sizeof *request);
	if (request == NULL)
		return (NULL);
	request->fields = fields;
	request->next = NULL;
	return (request);
}

static void	push_request(t_request *first, t_request *new)
{
	t_request	*request;

	request = first;
	while (request->next != NULL)
		request = request->next;
	request->next = new;
}

static int	open_database_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "ERROR: Could not open monitoring.db\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
