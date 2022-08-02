#include "monitoring.h"

void	write_log_head(t_request *request, FILE *log_file, char *protocol)
{
	char	*time;

	fprintf(log_file, "%s|%s|%s|%s",
		time, request->fields[NAME], protocol, request->fields[URL]);
}
