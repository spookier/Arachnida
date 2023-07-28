#include "scorpion.h"

/*
	* jpeg files start with: 	FF D8 FF
	* and end with:				FF D9
*/

// If file is JPG, it will return 1, else 0
int check_if_jpg(t_all *all)
{
	size_t i 						= 0;
	unsigned char start_hexa_JPG[3] = {0xFF, 0xD8, 0xFF};
	unsigned char end_hexa_JPG[2] 	= {0xFF, 0xD9};


	while (all->image[i] && i < 3)
	{
		if(all->image[i] != start_hexa_JPG[i])
			return(0);
		i++;
	}

	if (all->image[all->file_length - 2] != end_hexa_JPG[0])
		return(0);
	if(all->image[all->file_length - 1] != end_hexa_JPG[1])
		return(0);
	
	return(1);
}


int find_exif_jpg(t_all *all)
{
	
}