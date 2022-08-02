#include "monitoring.h"

static void	print_simple_head(t_request *request, char *time);
static void	print_in_blue(char *message);
static void	print_in_red(char *message);
static void	print_in_green(char *message);

void	print_simple_http(t_request *request, char *time, int is_healthy)
{
	print_simple_head(request, time);
	print_in_blue("Latency:");
	if (request->latency == 0)
		print_in_red("TIMEOUT");
	else
		printf("%.1f ms\n", request->latency * 1000);
	print_in_blue("Status:");
	if (is_healthy == TRUE)
		print_in_green("HEALTHY");
	else
		print_in_red("UNHEALTHY");
}

void	print_simple_dns(t_request *request, char *time, int is_healthy)
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

void	print_simple_ping(t_request *request, char *time, int is_healthy)
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
	print_in_blue("Protocol:");
	printf("%s\n", request->fields[PROTOCOL]);
	print_in_blue("Data:");
	printf("%s\n", time);
}

static void	print_in_blue(char *message)
{
	printf("\033[34;1m%s\033[0m ", message);
}

static void	print_in_red(char *message)
{
	printf("\033[0;31m%s\033[0m\n", message);
}

static void	print_in_green(char *message)
{
	printf("\033[0;32m%s\033[0m\n", message);
}
