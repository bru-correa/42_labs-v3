#include "monitoring.h"

// TODO Struct to handle each protocol

void	test_http_req(char *name, char *url, char *method, long expected)
{
	long	response;
	if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0)
		url = set_url_prefix(url);
	if (strcmp(method, "GET") == 0)
		response = check_http_get(url);
	else if (strcmp(method, "POST") == 0)
		response = check_http_post(url);
	write_http_log(name, response, expected, "monitoring.log", url);
}

char	*set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = strcat(url, "http://");
	free(url);
	return (url_with_prefix);
}

long	check_http_get(char *url)
{
	CURL	*curl;
	long	response_code;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	curl_easy_cleanup(curl);
	return (response_code);
}

long	check_http_post(char *url)
{
	CURL	*curl;
	long	response_code;

	curl = curl_easy_init();

	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=monitoring");
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	printf("\n%ld\n", response_code);
	curl_easy_cleanup(curl);
	return (response_code);
}

void	write_http_log(char *name, long response, long expected,
	char *filename, char *url)
{
	FILE	*file;
	char	*time;

	file = fopen(filename, "a");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}
	time = get_time();
	fprintf(file, "%s|%s|HTTP|%s|GET|Response:%ld|Expected:%ld|",
		time, name, url, response, expected);
	if (response != expected)
		fprintf(file, "UNHEALTHY\n");
	else
		fprintf(file, "HEALTHY\n");
	fclose(file);
}
