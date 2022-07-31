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
	time_str[ft_strlen(time_str) - 1] = '\0';
	return (time_str);
}
