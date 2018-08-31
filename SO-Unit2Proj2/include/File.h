#ifndef FILE_H_
#define FILE_H_

#include "Image.h"

/**
 * @brief 	Take the image of the archive 
 * @param 	archiveName		The archive name
 * @return 	img 			The image read
 */
Image* readImg (string archiveName);

/**
 * @brief 	Write the image in a archive 
 * @param 	img 			The image
 * @param 	archiveName		The archive name
 */
void writeImg(Image* img, string archiveName);

/**
 * @brief 	Convert a image in string 
 * @param 	image 		The image string
 * @return 	img 		The image created
 */
Image* from_string (string image);

#endif