#include "monitoring.h"

static t_overview	*get_next_overview(int database_fd);
static void			print_overview(t_overview *overview);
static void			get_overview_data(t_overview *overview);
static void			check_status(char **log_data, t_overview *overview);

void	print_overviews(void)
{
	int			database_fd;
	t_overview	*overview;

	database_fd = open("monitoring.db", O_RDONLY);
	overview = get_next_overview(database_fd);
	while (overview != NULL)
	{
		print_overview(overview);
		free(overview->name);
		free(overview);
		overview = get_next_overview(database_fd);
	}
	close(database_fd);
}

static t_overview	*get_next_overview(int database_fd)
{
	char		*line;
	char		**db_data;
	t_overview	*overview;

	line = ft_get_next_line(database_fd);
	if (line == NULL)
		return (NULL);
	overview = malloc(sizeof overview);
	db_data = ft_split(line, '\t');
	overview->name = ft_strdup(db_data[NAME]);
	overview->healthy_count = 0;
	overview->unhealthy_count = 0;
	free(line);
	free_matrix(db_data);
	return (overview);
}

static void	print_overview(t_overview *overview)
{
	get_overview_data(overview);
	print_divider();
	print_in_blue("Name:");
	printf("%s\n", overview->name);
	print_in_blue("Healthy:");
	print_in_green(ft_itoa(overview->healthy_count));
	print_in_blue("Unhealthy:");
	print_in_red(ft_itoa(overview->unhealthy_count));
}

static void	get_overview_data(t_overview *overview)
{
	int		log_fd;
	char	*line;
	char	**log_data;

	log_fd = open("monitoring.log", O_RDONLY);
	if (log_fd == -1)
	{
		fprintf(stderr, "ERROR: Could not open monitoring.log\n");
		exit(EXIT_FAILURE);
	}
	line = ft_get_next_line(log_fd);
	while (line != NULL)
	{
		log_data = ft_split(line, '|');
		if (ft_strncmp(log_data[LOG_NAME], overview->name,
			ft_strlen(overview->name) + 1) == 0)
			check_status(log_data, overview);
		free_matrix(log_data);
		free(line);
		line = ft_get_next_line(log_fd);
	}
	close(log_fd);
}

static void	check_status(char **log_data, t_overview *overview)
{
	if (ft_strncmp(log_data[LOG_PROTOCOL], "HTTP", 5) == 0)
	{
		if (ft_strncmp(log_data[LOG_HTTP_STATUS], "HEALTHY\n", 8) == 0)
			overview->healthy_count++;
		else
			overview->unhealthy_count++;
	}
	else if (ft_strncmp(log_data[LOG_PROTOCOL], "DNS", 4) == 0)
	{
		if (ft_strncmp(log_data[LOG_DNS_STATUS], "HEALTHY\n", 8) == 0)
			overview->healthy_count++;
		else
			overview->unhealthy_count++;
	}
	else if (ft_strncmp(log_data[LOG_PROTOCOL], "PING", 5) == 0)
	{
		if (ft_strncmp(log_data[LOG_PING_STATUS], "HEALTHY\n", 8) == 0)
			overview->healthy_count++;
		else
			overview->unhealthy_count++;
	}
}
