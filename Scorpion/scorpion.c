#include "scorpion.h"

/* -------------------------------------------
	TODO: Parse the following extensions:

* 1 .jpg/jpeg -> current
* 2 .png
* 3 .gif
* 4 .bmp
------------------------------------------- */


int detect_image_extension(t_all *all)
{
	if (check_if_jpg(all) == 1)
	{
		all->img_type = 0;
		find_exif_jpg(all);
		if(get_endianness(all, all->exif_parse.start_addr) == -1)
			return(-1);
	}
	else
	{
		printf("Error. Wrong or unsupported image extension.\n");
		return(-1);
	}
	return(0);
}


int main(int argc, char **argv)
{
	t_all *all;

	if (argc != 2)
	{
		printf("Incorrect arguments. Usage: %s <file>\n", argv[0]);
		return (-1);
	}

	if(init_structure(&all) == -1)
		return(-1);

	if (open_file(argv[1], all) == -1)
		return (-1);

	if (detect_image_extension(all) == -1)
		return(-1);

	// TODO: Free everything before program ends

	return(0);
}