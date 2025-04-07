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
	printf("Arguments ok, here the config_file parsing function should be called\n");
	printf("config file name: %s\n", argv[2]);
	return(EXIT_SUCCESS);
}
