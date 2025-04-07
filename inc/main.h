#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include "list_utils.h"
# include "config_file.h"

# define MAX_NUM 10000

typedef pthread_mutex_t mutex_t;

typedef struct data_s
{
	mutex_t		mutex_even;
	mutex_t		mutex_odd;
	list_t		*even_list;
	list_t		*odd_list;
	pthread_t	*threads;
	config_t	config;

} data_t;

#endif