#include "scorpion.h"


int open_file(char *PATH, t_all *all)
{
	FILE 			*file;
	unsigned char 	buffer[1024];
	unsigned char 	*tmp;
	size_t 			bytesRead;

	file = fopen(PATH, "rb");
	if (file == NULL)
	{
		printf("Error opening file.\n");
		return(-1);
	}

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
		tmp = realloc(all->image, all->file_length + bytesRead);
		if (tmp == NULL)
		{
			// TODO: Free if error... etc 
			return(-1);
		}
		all->image = tmp;
		memcpy(all->image + all->file_length, buffer, bytesRead);
		all->file_length += bytesRead;
	}
	// @DEBUG
	printf("File size = %ldkb\n", all->file_length);

	fclose(file);
	return(0);
}


int init_structure(t_all **structure)
{
    *structure = (t_all *)malloc(sizeof(t_all));
    if(!(*structure))
    {
        printf("Failed to allocate memory for the initial structure.\n");
        return(-1);
    }

    (*structure)->image = NULL;
    (*structure)->file_length = 0;

    return(0);
}
