#include "config_file.h"

/*
 * This function scans the file "filename": checks if it has the correct extension ".txt" and
 * if it has the correct format parameter=value, storing the values in the config struct.
 * Returns true if everything is ok, and false if something is wrong.
*/
bool	parse_config(const char *filename, config_t *config)
{
	const char	*ext = strrchr(filename, '.');

	if (!ext || strcmp(ext, ".txt"))
	{
		fprintf(stderr, "Error: config file must have .txt extension\n");
		return (false);
	}

	FILE	*file = fopen(filename, "r");

	if (!file)
	{
		fprintf(stderr, "Error: file %s does not exist or have read permission", filename);
		return (false);
	}

	char line[256];

	while (fgets(line, sizeof(line), file))
	{
		if (!strncmp(line, "numbers_per_thread", 10))
		{
			char	*equal_sign_ptr = strchr(line, '=');

			if (!equal_sign_ptr)
			{
				fprintf(stderr, "Error: config file format is unvalid\n");
				fclose(file);
				return (false);
			}
			config->numbers_per_thread = atoi(equal_sign_ptr + 1);
		}
		else if (strncmp(line, "thread_num", 10) == 0) 
		{
			char *equal_sign_ptr = strchr(line, '=');

			if (!equal_sign_ptr)
			{
				fprintf(stderr, "Error: config file format is unvalid\n");
				fclose(file);
				return (false);
			}	
			config->thread_num = atoi(equal_sign_ptr + 1);
		}
	}
	fclose(file);
	if (config->numbers_per_thread > 0 && config->thread_num > 0)
		return (true);
	fprintf(stderr, "Error: config file format is unvalid\n");
	return (false);
}
