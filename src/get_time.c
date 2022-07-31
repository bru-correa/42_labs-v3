#include "monitoring.h"

// TODO Fix the \n at the end
char	*get_time(void)
{
	time_t		raw_time;
	struct tm	*time_info;
	char		*time_str;

	time(&raw_time);
	time_info = localtime(&raw_time);
	time_str = asctime(time_info);
	return (time_str);
}
