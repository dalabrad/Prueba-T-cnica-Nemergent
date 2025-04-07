#ifndef CONFIG_FILE_H
# define CONFIG_FILE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

typedef struct config_s
{
	int	numbers_per_thread;
	int	thread_num;
}	config_t;

bool	parse_config(const char *filename, config_t *config);

#endif
