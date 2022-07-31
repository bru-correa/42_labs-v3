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

/********** MACROS **********/
# define LOGFILE "monitoring.log"
# define NAME 0
# define PROTOCOL 1
# define URL 2
# define HTTP_METHOD 3
# define HTTP_CODE 4
# define HTTP_INTERVAL 5
# define PING_INTERVAL 3
# define DNS_INTERVAL 3
# define DNS_SERVER 4

/********** STRUCTS **********/
typedef struct s_request
{
	char	**fields;
	int		interval_counter;
	long	response_code;
	void	*next;
}	t_request;

/********** PROTOTYPES **********/
char		*get_time(void);
void		request_http(t_request *request, FILE *log_file);
char		**get_next_fields(int database_fd);
t_request	*get_requests(char *database_filename);
void		stop_monitoring(t_request *first_request, FILE *log_file);
void		free_requests(t_request *first_request);

#endif
