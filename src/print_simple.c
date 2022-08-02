#include "monitoring.h"

static void	print_simple_head(t_request *request, char *time);

void	print_simple(t_request *request, char *time, int is_healthy)
{
	print_simple_head(request, time);
	print_in_blue("Latency:");
	if (request->latency == 0)
		print_in_red("TIMEOUT");
	else
		printf("%.1f ms\n", request->latency);
	print_in_blue("Status:");
	if (is_healthy == TRUE)
		print_in_green("HEALTHY");
	else
		print_in_red("UNHEALTHY");
}

static void	print_simple_head(t_request *request, char *time)
{
	printf("----------------------------------------\n");
	print_in_blue("Name:");
	printf("%s\n", request->fields[NAME]);
	print_in_blue("Address:");
	printf("%s\n", request->fields[URL]);
	print_in_blue("Protocol:");
	printf("%s\n", request->fields[PROTOCOL]);
	print_in_blue("Date:");
	printf("%s\n", time);
}
