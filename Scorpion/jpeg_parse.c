#include "scorpion.h"

/*
	* jpeg files start with: 	FF D8 FF
	* and end with:				FF D9
*/

int check_if_jpg(t_all *all)
{
	size_t i;
	unsigned char start_hexa_JPG[3] = {0xFF, 0xD8, 0xFF};
	unsigned char end_hexa_JPG[2] = {0xFF, 0xD9};

	i = 0;
	while (all->image && i < 3)
	{
		if(all->image[i] != start_hexa_JPG[i])
			return(0);
		i++;
	}

	i = all->file_length;
	i -= 2;
	while (all->image && i < 3)
	{
		if(all->image[i] != end_hexa_JPG[i])
			return(0);
		i++;
	}
	return(1);
}