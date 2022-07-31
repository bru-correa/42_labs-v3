#include "monitoring.h"

static char	*get_shell_cmds(char *dns_server, char *url);

void	lookup_dns(t_request *request, FILE *log_file)
{
	char	*shell_cmds;
	int		exit_code;

	shell_cmds = get_shell_cmds(request->fields[DNS_SERVER],
		request->fields[URL]);
	exit_code = system(shell_cmds);
	free(shell_cmds);
	if (exit_code != 0)
		fprintf(log_file, "UNHEALTHY\n");
}

static char	*get_shell_cmds(char *dns_server, char *url)
{
	char	*dig_cmd;
	char	*current_cmd_str;
	char	*prevous_cmd_str;

	dig_cmd = ft_strdup("dig @");
	current_cmd_str = ft_strjoin(dig_cmd, dns_server);
	free(dig_cmd);
	prevous_cmd_str = current_cmd_str;
	current_cmd_str = ft_strjoin(current_cmd_str, " ");
	free(prevous_cmd_str);
	prevous_cmd_str = current_cmd_str;
	current_cmd_str = ft_strjoin(current_cmd_str, url);
	free(prevous_cmd_str);
	prevous_cmd_str = current_cmd_str;
	current_cmd_str = ft_strjoin(current_cmd_str, " +noall +comments +comments\
		+timeout=2 | awk 'FNR == 2 {print $6}' | tr -d ,");
	free(prevous_cmd_str);
	return (current_cmd_str);
}
