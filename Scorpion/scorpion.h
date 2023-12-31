#ifndef SCORPION_H
# define SCORPION_H

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct s_ExifParse
{
    size_t  start_addr;
    int     little_endian;
    int     IFD_entries;

}   t_ExifParse;

typedef struct s_gpsData 
{
    float 		latitude;
    float 		longitude;

} t_gpsData;

typedef struct s_dateTime 
{
    int 		year;
    int 		month;
    int 		day;
    int 		hour;
    int 		minute;
    int 		second;

} t_dateTime;

typedef struct s_ExifData 
{
 	char 		cameraMake[32];
    char 		cameraModel[32];
    int 		isoSpeed;
    float 		exposureTime;
    float 		aperture;
    float 		focalLength;
	t_dateTime	dateTime;
	t_gpsData	gpsData;

}	t_ExifData;


typedef struct s_all
{
    unsigned char	*image; 	    // Entire binary image will be saved here
	size_t 			file_length;    // Size of image stored here

    int             img_type;       // *  0 = jpg/jpeg | 1 = png | 2 = gif | 3 = bmp 

    t_ExifData      exif_data;
    t_ExifParse     exif_parse;
    
} t_all;


// Open initial image and copy it in memory
int     open_file(char *PATH, t_all *all);

// Malloc initial struct
int     init_structure(t_all **structure);

// JPG Processing
int       check_if_jpg(t_all *all);
int       find_exif_jpg(t_all *all);
int       get_endianness(t_all *all, int start);
unsigned  int read_bytes(t_all *all, int start, int length, int little_endian);


#endif