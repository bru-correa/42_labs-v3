#include "monitoring.h"

static t_protocol	*create_protocol(char **data);
static void			push_protocol(t_protocol *first, t_protocol *new);
static void			free_protocols(t_protocol *first);
static void			free_protocol_data(char **data);

// ! Maybe change protocol to test so you dont get confuse between the two terms
// ! Get a better name for protocol/test
// ? test_query?

t_protocol	*get_protocols(int database_fd)
{
	char		**protocol_data;
	t_protocol	*first_protocol;
	t_protocol	*new_protocol;

	protocol_data = get_next_protocol_data(database_fd);
	if (protocol_data == NULL)
	{
		fprintf(stderr, "ERROR: Empty database\n");
		exit(EXIT_FAILURE);
	}
	first_protocol = create_protocol(protocol_data);
	protocol_data = get_next_protocol_data(database_fd);
	while (protocol_data != NULL)
	{
		new_protocol = create_protocol(protocol_data);
		push_protocol(first_protocol, new_protocol);
		protocol_data = get_next_protocol_data(database_fd);
	}
	return (first_protocol);
}

// TODO Maybe create the interval counter here (need to analyze protocol)
static t_protocol	*create_protocol(char **data)
{
	t_protocol	*protocol;

	protocol = malloc(sizeof *protocol);
	if (protocol == NULL)
		return (NULL);
	protocol->data = data;
	protocol->next = NULL;
	return (protocol);
}

static void	push_protocol(t_protocol *first, t_protocol *new)
{
	t_protocol	*protocol;

	protocol = first;
	while (protocol->next != NULL)
		protocol = protocol->next;
	protocol->next = new;
}

static void	free_protocols(t_protocol *first)
{
	t_protocol	*current;
	t_protocol	*previous;

	current = first;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		free_protocol_data(previous->data);
		free(previous);
	}
}

static void	free_protocol_data(char **data)
{
	int	i;

	i = 0;
	while (data[i] != NULL)
	{
		free(data[i]);
		i++;
	}
	free(data);
}
