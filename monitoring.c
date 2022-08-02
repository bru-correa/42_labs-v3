#include "monitoring.h"

static FILE	*open_log_file(char *filename);
static void	read_args(int argc, char *argv[]);

// TODO Read CLI arguments
int	main(int argc, char *argv[])
{
	read_args(argc, argv);
	return (0);
}

static FILE	*open_log_file(char *filename)
{
	FILE	*log_file;

	log_file = fopen(filename, "a");
	if (log_file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}
	return (log_file);
}

static void	read_args(int argc, char *argv[])
{
	FILE		*log_file;
	int			log_fd;
	t_request	*first_request;

	if (argc == 1)
	{
		log_file = open_log_file("monitoring.log");
		first_request = get_requests("monitoring.db");
		curl_global_init(CURL_GLOBAL_ALL);
		start_monitoring(first_request, log_file);
		stop_monitoring(first_request, log_file);
		curl_global_cleanup();

	}
	if (ft_strncmp(argv[1], "--simplified", 13) == 0)
	{
		log_fd = open("monitoring.log", O_RDONLY);
		read_simple(log_fd);
		close(log_fd);
		exit(EXIT_SUCCESS);
	}
}
