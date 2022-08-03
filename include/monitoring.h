#ifndef MONITORING_H
# define MONITORING_H

/********** INCLUDE **********/
# include <stdio.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "libft.h"
# include <fcntl.h>
# include <wait.h>

/********** MACROS **********/
# define NAME 0
# define PROTOCOL 1
# define URL 2
# define HTTP_METHOD 3
# define HTTP_CODE 4
# define HTTP_INTERVAL 5
# define PING_INTERVAL 3
# define DNS_INTERVAL 3
# define DNS_SERVER 4

# define CHILD_ID 0
# define READ_END 0
# define WRITE_END 1

# define LOG_DATE 0
# define LOG_NAME 1
# define LOG_PROTOCOL 2
# define LOG_URL 3
# define LOG_HTTP_LATENCY 7
# define LOG_HTTP_STATUS 8
# define LOG_DNS_LATENCY 6
# define LOG_DNS_STATUS 7
# define LOG_PING_LATENCY 4
# define LOG_PING_STATUS 5

/********** STRUCTS **********/
// Store request data from the monitoring.db
typedef struct s_request
{
	char	**fields;
	int		interval_counter;
	long	response_code;
	double	latency;
	void	*next;
}	t_request;

// Store how many times each request name have passed or failed
typedef struct s_overview
{
	char	*name;
	int		healthy_count;
	int		unhealthy_count;
}	t_overview;

/********** PROTOTYPES **********/
void		read_args(int argc, char *argv[]);
char		*get_time(void);
void		request_http(t_request *request, FILE *log_file);
char		**get_next_fields(int database_fd);
t_request	*get_requests(char *database_filename);
void		stop_monitoring(t_request *first_request, FILE *log_file);
void		free_matrix(char **matrix);
void		free_requests(t_request *first_request);
void		lookup_dns(t_request *request, FILE *log_file);
void		pipe_and_fork(int *pipe_fd, pid_t *pid);
void		redir_pipe_to_stdout(int *pipe_fd);
char		*get_dns_response(t_request *request, int data_file);
void		request_ping(t_request *request, FILE *log_file);
double		get_ping_latency(int data_file);
void		start_monitoring(t_request *first_request, FILE *log_file);
void		write_log_head(t_request *request, FILE *log_file, char *time);
void		print_simple(t_request *request, char *time, int is_healthy);
void		read_simple(void);
void		print_overviews(void);
void		print_in_blue(char *message);
void		print_in_red(char *message);
void		print_in_green(char *message);
void		print_divider(void);
void		set_url_prefix(char *url);
size_t		ignore_curl_output(void *buffer, size_t size, size_t nmemb,
	void*userp);

#endif
