#include "monitoring.h"

static void	set_url_prefix(char *url);
static long	check_http_request(t_request *request);
static void	write_http_log(t_request *request, FILE *log_file);
static size_t	ignore_output(void *buffer, size_t size, size_t nmemb,
	void*userp);

void	request_http(t_request *request, FILE *log_file)
{
	if (ft_strncmp(request->fields[URL], "http://", 7) == 0
		|| ft_strncmp(request->fields[URL], "https://", 8) == 0)
		set_url_prefix(request->fields[URL]);
	request->response_code = check_http_request(request);
	write_http_log(request, log_file);
}

static void	set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = ft_strjoin(url, "http://");
	free(url);
	url = url_with_prefix;
}

// TODO Hide output in stdout
static long	check_http_request(t_request *request)
{
	CURL	*curl;
	long	response_code;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	curl_easy_setopt(curl, CURLOPT_URL, request->fields[URL]);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request->fields[HTTP_METHOD]);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ignore_output);
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	curl_easy_cleanup(curl);
	return (response_code);
}

static void	write_http_log(t_request *request, FILE *log_file)
{
	char	*time;
	long	expected_code;

	time = get_time();
	expected_code = ft_atoi(request->fields[HTTP_CODE]);
	fprintf(log_file, "%s|%s|HTTP|%s|%s|Response:%ld|Expected:%ld|",
		time, request->fields[NAME], request->fields[URL],
		request->fields[HTTP_METHOD], request->response_code, expected_code);
	if (request->response_code != expected_code)
		fprintf(log_file, "UNHEALTHY\n");
	else
		fprintf(log_file, "HEALTHY\n");
}

/**
 * @brief This function is used exclusively as a callback in CURLOPT_WRITEDATA
 * to ignore the standard output from libcurl
 * @param buffer The output it would print to standard output
 * @param size Size is always 1
 * @param nmemb The size of the data in 'buffer'
 * @param userp Points to additional data retrieved by the callback
*/
static size_t	ignore_output(void *buffer, size_t size, size_t nmemb,
	void*userp)
{
	buffer = buffer;
	userp = userp;
	return (size *nmemb);
}
