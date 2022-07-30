#include "monitoring.h"

long	check_http_get(char *url)
{
	CURL		*curl;
	long		response_code;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	curl_easy_cleanup(curl);
	return (response_code);
}

void	write_http_log(long response, long expected, char *filename, char *url)
{
	FILE	*file;
	char	*time;

	file = fopen(filename, "w");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}
	time = get_time();
	fprintf(file, "%sHTTP %s GET Response:%ld Expected:%ld ",
		time, url, response, expected);
	if (response != expected)
		fprintf(file, "UNHEALTHY");
	else
		fprintf(file, "HEALTHY");
}
