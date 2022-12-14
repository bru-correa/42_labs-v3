#include "monitoring.h"

void	stop_monitoring(t_request *first_request, FILE *log_file)
{
	fclose(log_file);
	free_requests(first_request);
	curl_global_cleanup();
}

void	free_requests(t_request *first_request)
{
	t_request	*current_request;
	t_request	*previous_request;

	current_request = first_request;
	while (current_request != NULL)
	{
		previous_request = current_request;
		current_request = current_request->next;
		free_matrix(previous_request->fields);
		free(previous_request);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
