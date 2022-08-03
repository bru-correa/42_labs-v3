#include "monitoring.h"

static void	check_simplified(char *arg);
static void	check_overview(char *arg);

void	read_args(int argc, char *argv[])
{
	int		i;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i] != NULL)
	{
		check_simplified(argv[i]);
		check_overview(argv[i]);
		i++;
	}
}

static void	check_simplified(char *arg)
{
	if (ft_strncmp(arg, "--simplified", 13) == 0)
	{
		read_simple();
		exit(EXIT_SUCCESS);
	}
}

static void	check_overview(char *arg)
{
	if (ft_strncmp(arg, "--overview", 11) == 0)
	{
		print_overviews();
		exit(EXIT_SUCCESS);
	}
}
