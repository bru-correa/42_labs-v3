#include "monitoring.h"

char	*get_date(void)
{
	time_t		raw_time;
	struct tm	*time_info;
	char		*date;

	time(&raw_time);
	time_info = localtime(&raw_time);
	date = asctime(time_info);
	date[ft_strlen(date) - 1] = '\0';
	return (date);
}
