#include "monitoring.h"

int	main(void)
{
	test_http_req("google POST", "google.com", "POST", 200);
	test_http_req("intra test", "intra.42.fr", "GET", 200);
	return (0);
}
