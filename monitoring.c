#include "monitoring.h"

static FILE	*open_log_file(char *filename);

int	main(int argc, char *argv[])
{
	FILE		*log_file;
	t_request	*first_request;

	read_args(argc, argv);
	log_file = open_log_file("monitoring.log");
	first_request = get_requests("monitoring.db");
	curl_global_init(CURL_GLOBAL_ALL);
	start_monitoring(first_request, log_file);
	stop_monitoring(first_request, log_file);
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
