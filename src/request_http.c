#include "monitoring.h"

static CURL	*setup_curl(t_request *request);
static void	perform_http_request(CURL *curl, t_request *request);
static void	write_http_log(t_request *request, FILE *log_file);
static void	write_http_log_status(t_request *request, FILE *log_file,
	char *time);

void	request_http(t_request *request, FILE *log_file)
{
	CURL	*curl;

	curl = setup_curl(request);
	perform_http_request(curl, request);
	write_http_log(request, log_file);
}

static CURL	*setup_curl(t_request *request)
{
	CURL	*curl;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "ERROR: Failed to init curl\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(request->fields[URL], "http://", 7) == 0
		|| ft_strncmp(request->fields[URL], "https://", 8) == 0)
		set_url_prefix(request->fields[URL]);
	curl_easy_setopt(curl, CURLOPT_URL, request->fields[URL]);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request->fields[HTTP_METHOD]);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ignore_curl_output);
	return (curl);
}

static void	perform_http_request(CURL *curl, t_request *request)
{
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &(request->response_code));
	curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &(request->latency));
	request->latency *= 1000;
	curl_easy_cleanup(curl);
}

static void	write_http_log(t_request *request, FILE *log_file)
{
	char	*time;

	time = get_time();
	write_log_head(request, log_file, time);
	fprintf(log_file, "%s|%ld|%s|", request->fields[HTTP_METHOD],
		request->response_code, request->fields[HTTP_CODE]);
	if (request->response_code == 0)
		fprintf(log_file, "TIMEOUT|");
	else
		fprintf(log_file, "%.1f ms|", request->latency);
	write_http_log_status(request, log_file, time);
	fflush(log_file);
}

static void	write_http_log_status(t_request *request, FILE *log_file,
	char *time)
{
	int	expected_code;

	expected_code = ft_atoi(request->fields[HTTP_CODE]);
	if (request->response_code != expected_code)
	{
		fprintf(log_file, "UNHEALTHY\n");
		print_simple(request, time, FALSE);
	}
	else
	{
		fprintf(log_file, "HEALTHY\n");
		print_simple(request, time, TRUE);
	}
}
