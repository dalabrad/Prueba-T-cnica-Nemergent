#include "main.h"

void	*thread_routine(void *arg)
{
	data_t *data = (data_t *)arg;
	int		n = data->config.numbers_per_thread;

	for (int i = 0; i < n; i++)
	{
		int num = rand() % MAX_NUM;

		if (num % 2 == 0)
		{
			pthread_mutex_lock(&(data->mutex_even));
			if (!data->even_list) //check if even list still allocated
			{
				pthread_mutex_unlock(&(data->mutex_even));
				return (NULL);
			}
			if (add_to_list(data->even_list, num)) // if new node append fails the list is freed
			{
				pthread_mutex_unlock(&(data->mutex_even));
				return (NULL);
			}
			pthread_mutex_unlock(&(data->mutex_even));
		}
		else
		{
			pthread_mutex_lock(&(data->mutex_odd));
			if (!data->odd_list) //check if odd list still allocated
			{
				pthread_mutex_unlock(&(data->mutex_odd));
				return (NULL);
			}
			if (add_to_list(data->odd_list, num)) // if new node append fails the list is freed
			{
				pthread_mutex_unlock(&(data->mutex_odd));
				return (NULL);
			}
			pthread_mutex_unlock(&(data->mutex_odd));
		}
	}
	return (NULL);
}

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

	data_t data;

	if (!parse_config(argv[2], &(data.config)))
		return (EXIT_FAILURE);

	srand(time(NULL) * getpid()); //Generate rand seed.

	// Init mutexes and check for correct initialization.
	if (pthread_mutex_init(&(data.mutex_even), NULL))
	{
		fprintf(stderr, "Error: mutex: unable to initialize mutex\n");
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(data.mutex_odd), NULL))
	{
		fprintf(stderr, "Error: mutex: unable to initialize mutex\n");
		pthread_mutex_destroy(&(data.mutex_odd));
		return (EXIT_FAILURE);
	}

	// Init list and check the data allocation
	data.even_list = create_list();
	if (!data.even_list)
	{
		fprintf(stderr, "Error: malloc: data allocation failed\n");
		pthread_mutex_destroy(&(data.mutex_even));
		pthread_mutex_destroy(&(data.mutex_odd));
		return (EXIT_FAILURE);
	}
	data.odd_list = create_list();
	if (!data.odd_list)
	{
		fprintf(stderr, "Error: malloc: data allocation failed\n");
		free_list(data.even_list);
		pthread_mutex_destroy(&(data.mutex_even));
		pthread_mutex_destroy(&(data.mutex_odd));
		return (EXIT_FAILURE);
	}

	//	Allocate space for the array of threads and check allocation.
	data.threads = (pthread_t *)malloc(sizeof(pthread_t) * data.config.thread_num);
	if (!data.threads)
	{
		fprintf(stderr, "Error: malloc: data allocation failed\n");
		free_list(data.even_list);
		free_list(data.even_list);
		pthread_mutex_destroy(&(data.mutex_even));
		pthread_mutex_destroy(&(data.mutex_odd));
		return (EXIT_FAILURE);
	}

	//	Init threads
	int i = 0;

	for (;i < data.config.thread_num; i++)
	{
		if (pthread_create(&(data.threads[i]), NULL, thread_routine, &data))
		{
			fprintf(stderr, "Error: pthread: thread creation failed\n");
			break ;
		}
	}

	// Join threads
	for (int j = 0; j < i; j++)
	{
		pthread_join(data.threads[j], NULL);
	}

	// Print lists
	if (i == data.config.thread_num)
	{
		printf("Even number list:\n");
		print_list(data.even_list);
		printf("Odd number list:\n");
		print_list(data.odd_list);
	}

	// Free allocated data
	if (data.even_list)
		free_list(data.even_list);
	if (data.odd_list)
		free_list(data.odd_list);
	free(data.threads);

	//Destroy mutexes
	pthread_mutex_destroy(&data.mutex_even);
	pthread_mutex_destroy(&data.mutex_odd);

	return(EXIT_SUCCESS);
}

// TO DO: add another mutex to start all threads synchronized.

