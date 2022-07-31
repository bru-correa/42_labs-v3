#include "monitoring.h"

static void	set_url_prefix(char *url);
static long	check_http_request(t_http_data *http_data);
static void	write_http_log(t_http_data *http_data, char *log_filename);

void	test_http_req(t_http_data *http_data, char *log_filename)
{
	if (ft_strncmp(http_data->url, "http://", 7) == 0
		|| ft_strncmp(http_data->url, "https://", 8) == 0)
		set_url_prefix(http_data->url);
	http_data->response = check_http_request(http_data);
	write_http_log(http_data, log_filename);
	free_http_data(http_data);
}

static void	set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = ft_strjoin(url, "http://");
	free(url);
	url = url_with_prefix;
}

// TODO Hide output in stdout
static long	check_http_request(t_http_data *http_data)
{
	CURL	*curl;
	long	response;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, http_data->url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, http_data->method);
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
	curl_easy_cleanup(curl);
	return (response);
}

static void	write_http_log(t_http_data *http_data, char *log_filename)
{
	FILE	*file;
	char	*time;

	file = fopen(log_filename, "a");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open %s\n", log_filename);
		free_http_data(http_data);
		exit(EXIT_FAILURE);
	}
	time = get_time();
	fprintf(file, "%s|%s|HTTP|%s|%s|Response:%ld|Expected:%ld|",
		time, http_data->name, http_data->url, http_data->method,
		http_data->response, http_data->expected);
	if (http_data->response != http_data->expected)
		fprintf(file, "UNHEALTHY\n");
	else
		fprintf(file, "HEALTHY\n");
	fclose(file);
}
