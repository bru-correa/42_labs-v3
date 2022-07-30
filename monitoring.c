#include "monitoring.h"

int	main(void)
{
	int	exit_status;
	int	response_code;

	exit_status = system("dig @8.8.8.8 google.com +noall +comments +timeout=2 \
		| awk 'FNR == 2 {print $6}' | tr -d ,");
	exit_status = system("ping google.com -c1 | grep packet \
		| awk '{print $6}'");
	printf("Exit status: %d\n", exit_status);
	response_code = check_http_get("http://google.com");
	write_http_log(response_code, 200L, "monitoring.log", "http://google.com");
	return (0);
}
