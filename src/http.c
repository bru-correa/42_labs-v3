#include "monitoring.h"

void	test_http_req(t_http_data http_data, char *log_filename)
{
	if (strncmp(http_data.url, "http://", 7) == 0
		|| strncmp(http_data.url, "https://", 8) == 0)
		http_data.url = set_url_prefix(http_data.url);
	// if (strcmp(method, "GET") == 0)
	// 	response = check_http_get(url);
	// else if (strcmp(method, "POST") == 0)
	// 	response = check_http_post(url);
	http_data.response = check_http_request(http_data);
	write_http_log(http_data, log_filename);
}

char	*set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = strcat(url, "http://");
	free(url);
	return (url_with_prefix);
}

long	check_http_request(t_http_data http_data)
{
	CURL	*curl;
	long	response;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, http_data.url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, http_data.method);
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
	curl_easy_cleanup(curl);
	return (response);
}

void	write_http_log(t_http_data http_data, char *log_filename)
{
	FILE	*file;
	char	*time;

	file = fopen(log_filename, "a");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open %s\n", log_filename);
		exit(EXIT_FAILURE);
	}
	time = get_time();
	fprintf(file, "%s|%s|HTTP|%s|%s|Response:%ld|Expected:%ld|",
		time, http_data.name, http_data.url, http_data.method,
		http_data.response, http_data.expected);
	if (http_data.response != http_data.expected)
		fprintf(file, "UNHEALTHY\n");
	else
		fprintf(file, "HEALTHY\n");
	fclose(file);
}
