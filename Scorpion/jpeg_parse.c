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
	size_t i 					= 0;
	unsigned char exif_bytes[2] = {0xFF, 0xE1};

	while (all->image[i] && i < all->file_length)
	{
		if (i + 1 < all->file_length && all->image[i] == exif_bytes[0] && all->image[i + 1] == exif_bytes[1])
		{
			all->exif_parse.start_addr = i + 8;

			// @DEBUG
			// printf("Start address = %ld\n", all->exif_parse.start_addr);
			// printf("%02X\n", all->image[all->exif_parse.start_addr]);
			// printf("Next = %ld\n", all->exif_parse.start_addr + 1);
			// printf("%02X\n", all->image[all->exif_parse.start_addr + 1]);
			// printf("Next = %ld\n", all->exif_parse.start_addr + 2);
			// printf("%02X\n", all->image[all->exif_parse.start_addr + 2]);
			return(0);
		}
		i++;
	}
	printf("EXIF Marker not found.\n");
	return(-1);
}

int get_endianness(t_all *all, int start)
{
	start += 2;
	if (all->image[start] == 'I' && all->image[start + 1] == 'I')
	{
		//@DEBUG
		printf("Little endian.\n");
		all->exif_parse.little_endian = 1; // Little endian
	}
    else if (all->image[start] == 'M' && all->image[start + 1] == 'M')
	{
		//@DEBUG
		printf("Big endian.\n");
		all->exif_parse.little_endian = 2; // Big endian
	}
	else
	{
		printf("Error. Invalid endianness.\n");
		return (-1); // Invalid EXIF
	}

	return(0);
}


// start is the starting index of the bytes to read
// length is the number of bytes to read
// and little_endian is a boolean flag 
unsigned int read_bytes(t_all *all, int start, int length, int little_endian)
{
	unsigned int value;
	int i;
	
	value 	= 0;
	i 		= 0;

	if (little_endian) 
	{
		while (i < length)
		{
			value |= all->image[start + i] << (8 * i);
			i++;
		}
	} 
	else 
	{
		while (i < length)
		{
			value |= all->image[start + i] << (8 * (length - 1 - i));
			i++;
		}
	}
	return value;
}
