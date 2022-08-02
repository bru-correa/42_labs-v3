#include "monitoring.h"

void	write_log_head(t_request *request, FILE *log_file, char *time)
{
	fprintf(log_file, "%s|%s|%s|%s|",
		time, request->fields[NAME], request->fields[PROTOCOL],
		request->fields[URL]);
}
