#ifndef MONITORING_H
# define MONITORING_H

/********** INCLUDE **********/
# include <stdio.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <time.h>
# include "libft.h"
# include <fcntl.h>
# include <wait.h>

/********** MACROS **********/
# define NAME 0
# define PROTOCOL 1
# define URL 2
# define HTTP_METHOD 3
# define HTTP_CODE 4
# define HTTP_INTERVAL 5
# define PING_INTERVAL 3
# define DNS_INTERVAL 3
# define DNS_SERVER 4

# define CHILD_ID 0
# define READ_END 0
# define WRITE_END 1

# define LOG_DATE 0
# define LOG_NAME 1
# define LOG_PROTOCOL 2
# define LOG_URL 3
# define LOG_HTTP_LATENCY 7
# define LOG_HTTP_STATUS 8
# define LOG_DNS_LATENCY 6
# define LOG_DNS_STATUS 7
# define LOG_PING_LATENCY 4
# define LOG_PING_STATUS 5

/********** STRUCTS **********/
// Store request data from the monitoring.db
typedef struct s_request
{
	char	**fields;
	long	response_code;
	double	latency;
	char	*date;
	int		interval_counter;
	void	*next;
}	t_request;

// Store how many times each request name have passed or failed
typedef struct s_overview
{
	char	*name;
	int		healthy_count;
	int		unhealthy_count;
}	t_overview;

/********** PROTOTYPES **********/
/**
 * @brief Read the args from main to check for --simplified or --overview
 * @param argc main argc
 * @param argv main argv
*/
void		read_args(int argc, char *argv[]);
/**
 * @brief Get the current date and and remove the '\n' at the end
 * @return Current date string
*/
char		*get_date(void);
/**
 * @brief Create a pipe and fork
 * @param pipe_fd The address to store the pipe
 * @param pid The address to store the proccess id
*/
void		pipe_and_fork(int *pipe_fd, pid_t *pid);
/**
 * @brief Duplicate pipe write end to STDOUT and close the pipe
 * @param pipe_fd The pipe's address
*/
void		redir_pipe_to_stdout(int *pipe_fd);
/**
 * @brief Open the 'database' and retrieve the request list from it
 * @param database_filename The database name
 * @return Return the first request from the list of requests
*/
t_request	*get_requests(char *database_filename);
/**
 * @brief Get all the needed data to make requests from the 'database'
 * @param database_fd The database file descriptor
 * @return The data matrix retrieved from the 'database'
*/
char		**get_next_fields(int database_fd);
/**
 * @brief Setup libcurl, do a http request, and print the result in 'log_file'
 * @param request The request data
 * @param log_file The opened log file
*/
void		request_http(t_request *request, FILE *log_file);
/**
 * @brief Set a http:// prefix to 'url'
 * @param url The url to be prefixed test
*/
void		set_url_prefix(char *url);
/**
 * @brief Execute the dig command in the shell, parse the output and print the
 * result in 'log_file' * @param request The request data * @param log_file The opened log file
*/
void		lookup_dns(t_request *request, FILE *log_file);
/**
 * @brief Get the response code from the dns request
 * @param request The request data
 * @param data_file The opened read end from pipe
 * @return The response code
*/
char		*get_dns_response(t_request *request, int data_file);
/**
 * @brief Execute the ping command in the shell, parse the output and print the
 * result in 'log_file'
 * @param request The request data
 * @param log_file The opened log file
*/
void		request_ping(t_request *request, FILE *log_file);
/**
 * @brief Retrieve the ping latency in ms from the pipe read end 'data_file'
 * @param data_file The opened read end from pipe
 * @return The latency from the ping request in ms
*/
double		get_ping_latency(int data_file);
/**
 * @brief Monitor the request list and print the results in 'log_file'. It checks every minute if it can make a new request
 * @param first_request The first request from the list
 * @param log_file The opened log file
*/
void		start_monitoring(t_request *first_request, FILE *log_file);
/**
 * @brief Write to 'log_file' the date,the name, the protocol and the url from
 * the request
 * @param request The request data
 * @param log_file The opened log file
*/
void		write_log_head(t_request *request, FILE *log_file);
/**
 * @brief Print to STDOUT a simplified version of the log from the request
 * @param request The request data
 * @param is_healthy The health state of the request
*/
void		print_simple(t_request *request, int is_healthy);
/**
 * @brief Read from monitoring.log and print in STDOUT a simplified version of
 * the log
*/
void		read_simple(void);
/**
 * @brief Read from monitoring.log and print in STDOUT a general overview of
 * the results from all the requests in the log
*/
void		print_overviews(void);
/**
 * @brief Print in STDOUT the 'message' in bold and blue
 * @param message The message to be printed
*/
void		print_in_blue(char *message);
/**
 * @brief Print in STDOUT the 'message' in red and put a '\n' at the end
 * @param message The message to be printed
*/
void		print_in_red(char *message);
/**
 * @brief Print in STDOUT the 'message' in green and put a '\n' at the end
 * @param message The message to be printed
*/
void		print_in_green(char *message);
/**
 * @brief Print in STDOUT a line of dashes
*/
void		print_divider(void);
/**
 * @brief Stop monitoring the requests, free all the used memory from them,
 * close the log_file and cleanup curl
 * @param first_request The first request from the request list
 * @param log_file The log file to be closed
*/
void		stop_monitoring(t_request *first_request, FILE *log_file);
/**
 * @brief Free 2d array
 * @param matrix The 2d array to be freed
*/
void		free_matrix(char **matrix);
/**
 * @brief Free and the requests from the list
 * @param first_request The first request from the request list
*/
void		free_requests(t_request *first_request);
/**
 * @brief Used exclusively as a callback in CURLOPT_WRITEDATA to ignore the
 * standard output from libcurl
 * @param buffer The output it would print to standard output
 * @param size Size is always 1
 * @param nmemb The size of the data in 'buffer'
 * @param userp Points to additional data retrieved by the callback
 * @return 'size' * 'nmemb'
*/
size_t		ignore_curl_output(void *buffer, size_t size, size_t nmemb,
	void*userp);

#endif
