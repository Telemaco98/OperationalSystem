/**
 * @file	Image.h
 * @brief 	Archive to implements the methods of the class Image.
 *
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	13.11.2017
 * @data 	13.11.2017
 * @sa 		Image.h
 */

#include "Image.h"

/**
 * @brief 	The constructor of the image class
 * @param 	w 		The width
 * @param 	h 		The height
 * @param  	t 		The pixel type
 * @param 	p 		The pixel matrix
 */
Image::Image (int w, int h, PixelType t) {
	width = w;
	height = h;
	type = t;

	pixels = new Pixel *[width];
    for(int i = 0; i < width; i++) {
        pixels[i] = new Pixel [width];
        for(int j = 0; j < height; j++) {
            pixels[i][j].rgb.R = 0;
        	pixels[i][j].rgb.G = 0;
        	pixels[i][j].rgb.B = 0;
        	pixels[i][j].rgb.a = 0;
        }
	}
}

/** 
 * @brief 	Returns the width 
 * @return 	width 		The image width
 */
int Image::getWidth () {
	return width;
}

/**
 * @brief 	Return the height 
 * @return 	height 		The image height
 */
int Image::getHeight () {
	return height;
}

/**
 * @brief 	Return the type
 * @return 	type 		The image type 
 */
PixelType Image::getType () {
	return type;
}

/** 
 * @brief 	Return the image pixels 
 * @return 	pixels 		The pixel matrix
 */
Pixel** Image::getPixels () {
	return pixels;
}

/**
 * @brief Change the type value 
 */
void Image::setType (PixelType t) {
	if (t != type)  type = t;
}

/**
 * @brief Change the pixels value
 */
void Image::setPixels (Pixel** p) {
	pixels = p;
}

/**
 * @brief Convert Image to string 
 */
string Image::to_string () {
	string image;
	if (type == PixelType::RGB) image = "rgb ";
	else image = "ycbcr ";
	image += width + " " + height;

	for(int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++){
			if(type == PixelType::RGB) {
				image += " " + std::to_string(pixels[i][j].rgb.R);
				image += " " + std::to_string(pixels[i][j].rgb.G);
				image += " " + std::to_string(pixels[i][j].rgb.B);
			} else {
				image += " " + std::to_string(pixels[i][j].ycbcr.Y);
				image += " " + std::to_string(pixels[i][j].ycbcr.Cb);
				image += " " + std::to_string(pixels[i][j].ycbcr.Cr);
			}
		}
	}
	return image;
}

/** 
 * @brief Set a pixel in a posicion 
 * @param 	r 		The row
 * @param 	c 		The col
 * @param 	p 		The pixel
 */
void Image::setPixel (int r, int c, Pixel p) {
	pixels[r][c] = p;
}