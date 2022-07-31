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
void	test_http_req(t_http_data *http_data, char *log_filename);
void	free_http_data(t_http_data *http_data);

#endif
