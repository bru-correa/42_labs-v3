#include "monitoring.h"

static int	open_db(void);
static void	print_protocol(char **protocol);
static void	free_protocol(char **protocol);

int	main(void)
{
	int		fd;
	char	**protocol;

	curl_global_init(CURL_GLOBAL_ALL);
	fd = open_db();
	close(fd);
	curl_global_cleanup();
	return (0);
}

static int	open_db(void)
{
	int	fd;

	fd = open("monitoring.db", O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "ERROR: Could not open monitoring.db\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	test_https(t_protocol *first_protocol);

static void	print_protocol_data(char **protocol)
{
	int	current_data;

	if (protocol == NULL)
		return ;
	current_data = 0;
	while (protocol[current_data] != NULL)
	{
		printf("%s\n", protocol[current_data]);
		current_data++;
	}
}
