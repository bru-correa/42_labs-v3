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

/********** STRUCTS **********/
typedef struct s_request
{
	char	**fields;
	int		interval_counter;
	long	response_code;
	double	latency;
	void	*next;
}	t_request;

/********** PROTOTYPES **********/
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
void		print_simple(t_request *request, char *time, int is_healthy);
void		write_log_head(t_request *request, FILE *log_file, char *time);

#endif
