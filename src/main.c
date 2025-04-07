#include "main.h"

int	main(int argc, char *argv[])
{
	if (argc == 1 || argc > 3)
	{
		fprintf(stderr, "Error: wrong arguments. Use -h or --help for more info\n");
		return (EXIT_FAILURE);
	}
    
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        printf("Help: use %s -f <config_file.txt>\n", argv[0]);
        return (EXIT_SUCCESS);
    }
    
    if ((strcmp(argv[1], "-f") && strcmp(argv[1], "--file")) || argc != 3) 
    {
        fprintf(stderr, "Error: Wrong arguments. Use -h or --help for more info\n");
        return (EXIT_FAILURE);
    }

	config_t config;

	if (!parse_config(argv[2], &config))
		return (EXIT_FAILURE);
	printf("numbers_per_thread = %d\n", config.numbers_per_thread);
	printf("thread_num = %d\n", config.thread_num);
	return(EXIT_SUCCESS);
}
