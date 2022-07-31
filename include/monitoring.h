#ifndef MONITORING_H
# define MONITORING_H

/********** INCLUDE **********/
# include <stdio.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

/********** MACROS **********/
# define LOGFILE "monitoring.log"

/********** STRUCTS **********/
typedef struct s_http_data
{
	char	*name;
	char	*url;
	char	*method;
	long	response;
	long	expected;
}	t_http_data;

/********** PROTOTYPES **********/
char	*get_time(void);
void	write_http_log(t_http_data http_data, char *log_filename);
char	*set_url_prefix(char *url);
void	test_http_req(t_http_data http_data, char *log_filename);
long	check_http_request(t_http_data http_data);

#endif
