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

/********** PROTOTYPES **********/
char	*get_time(void);
long	check_http_get(char *url);
long	check_http_post(char *url);
void	write_http_log(char *name, long response, long expected,
	char *filename, char *url);
char	*set_url_prefix(char *url);
void	test_http_req(char *name, char *url, char *method, long expected);

#endif
