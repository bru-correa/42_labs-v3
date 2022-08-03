#include "monitoring.h"

void	print_in_blue(char *message)
{
	printf("\033[34;1m%s\033[0m ", message);
}

void	print_in_red(char *message)
{
	printf("\033[0;31m%s\033[0m\n", message);
}

void	print_in_green(char *message)
{
	printf("\033[0;32m%s\033[0m\n", message);
}

void	print_divider(void)
{
	printf("----------------------------------------\n");
}
