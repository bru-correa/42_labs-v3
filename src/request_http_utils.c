#include "monitoring.h"

void	set_url_prefix(char *url)
{
	char	*url_with_prefix;

	url_with_prefix = ft_strjoin(url, "http://");
	free(url);
	url = url_with_prefix;
}

size_t	ignore_curl_output(void *buffer, size_t size, size_t nmemb,
	void*userp)
{
	buffer = buffer;
	userp = userp;
	return (size *nmemb);
}
