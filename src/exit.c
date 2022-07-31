#include "monitoring.h"

void	free_http_data(t_http_data *http_data)
{
	free(http_data->name);
	free(http_data->method);
	free(http_data->url);
	free(http_data);
}
