#include "monitoring.h"

static FILE	*open_log_file(char *filename);

// TODO Read CLI arguments
int	main(void)
{
	t_request	*first_request;
	FILE		*log_file;

	curl_global_init(CURL_GLOBAL_ALL);
	first_request = get_requests("monitoring.db");
	log_file = open_log_file("monitoring.log");
	request_http(first_request, log_file);
	request_http(first_request->next, log_file);
	stop_monitoring(first_request, log_file);
	curl_global_cleanup();
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
