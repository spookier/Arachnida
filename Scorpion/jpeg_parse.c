#include "scorpion.h"

/*
	* jpeg files start with: 	FF D8 FF
	* and end with:				FF D9
*/

// If file is JPG, it will return 1, else -1
int check_if_jpg(t_all *all)
{
	size_t i 						= 0;
	unsigned char start_hexa_JPG[3] = {0xFF, 0xD8, 0xFF};
	unsigned char end_hexa_JPG[2] 	= {0xFF, 0xD9};

	while (all->image[i] && i < 3)
	{
		if(all->image[i] != start_hexa_JPG[i])
			return(-1);
		i++;
	}

	if (all->image[all->file_length - 2] != end_hexa_JPG[0])
		return(-1);
	if(all->image[all->file_length - 1] != end_hexa_JPG[1])
		return(-1);

	return(1);
}

/*
* If EXIF marker is present, it will start with: 0xFF 0xE1
* The actual EXIF data starts 8 bytes after the marker
*/

// If EXIF marker found, returns 0
int find_exif_jpg(t_all *all)
{
	size_t i 						= 0;
	unsigned char exif_bytes[2] = {0xFF, 0xE1};

	while (all->image[i] && i < all->file_length)
	{
		if(i + 1 < all->file_length && all->image[i] == exif_bytes[0] && all->image[i + 1] == exif_bytes[1])
		{
			all->exif_parse.start_addr = i + 8;
			// @DEBUG
			printf("Start address = %ld\n", all->exif_parse.start_addr);
			return(0);
		}
		i++;
	}
	printf("EXIF Marker not found.\n");
	return(-1);
}