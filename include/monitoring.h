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
# define ADDRESS 2
# define HTTP_METHOD 3
# define HTTP_CODE 4
# define HTTP_INTERVAL 5
# define PING_INTERVAL 3
# define DNS_INTERVAL 3
# define DNS_SERVER 4

/********** STRUCTS **********/
typedef struct s_http_data
{
	char	*name;
	char	*url;
	char	*method;
	long	response;
	long	expected;
}	t_http_data;

typedef struct s_protocol
{
	char	**data;
	int		interval_counter;
	void	*next;
}	t_protocol;

/********** PROTOTYPES **********/
char	*get_time(void);
void	test_http_req(t_http_data *http_data, char *log_filename);
void	free_http_data(t_http_data *http_data);
char	**get_next_protocol_data(int fd);
t_protocol	*get_protocols(int database_fd);

#endif
