#include "monitoring.h"

/**
 * @brief Set a http:// prefix to 'url'
 * @param url The url to be prefixed test
*/
void	set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = ft_strjoin(url, "http://");
	free(url);
	url = url_with_prefix;
}

/**
 * @brief Used exclusively as a callback in CURLOPT_WRITEDATA to ignore the
 * standard output from libcurl
 * @param buffer The output it would print to standard output
 * @param size Size is always 1
 * @param nmemb The size of the data in 'buffer'
 * @param userp Points to additional data retrieved by the callback
 * @return 'size' * 'nmemb'
*/
size_t	ignore_curl_output(void *buffer, size_t size, size_t nmemb,
	void*userp)
{
	buffer = buffer;
	userp = userp;
	return (size *nmemb);
}
