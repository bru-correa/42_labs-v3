#ifndef MONITORING_H
# define MONITORING_H

# include <stdio.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

# define LOGFILE "monitoring.log"

char	*get_time(void);
long	check_http_get(char *url);
void	write_http_log(long response, long expected, char *filename, char *url);

#endif
