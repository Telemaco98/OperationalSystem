/**
 * @file	Image.h
 * @brief 	Archive to create the class Image. The class fields are: width,
 * 			height, type and pixels.
 *
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	13.11.2017
 * @data 	13.11.2017
 */

#ifndef IMAGE_H_
#define IMAGE_H_ value

#include <iostream>

#include <string>
using std::string;

/** @enum PixelType */
enum class PixelType{
	RGB = 1, 	/** < RGB */ 
	YCbCr		/** < ycbcr */
};

typedef struct rgb { 
	int R, G, B, a;
}RGB;

typedef struct ycbcr {
	int Y, Cb, Cr, a;
}YCbCr;

typedef union pixel {
	RGB rgb;
	YCbCr ycbcr;
} Pixel;

/**
 * @class Image 
 */
class Image {
	private:
		int width; 		/**< The image width */
		int height;		/**< The image height */
		PixelType type; /**< The image type (1 == rgb, 2 = ycbcr) */
		Pixel** pixels; /**< The image pixels */

	public:
		/** @brief The constructor of the image class */
		Image (int w, int h, PixelType type);

		/** @brief Returns the image width */
		int getWidth ();

		/** @brief Returns the image height */
		int getHeight ();

		/** @brief Return the imgage type */
		PixelType getType ();

		/** @brief Return the image pixels */
		Pixel** getPixels ();
		
		/** @brief Change the type value */
		void setType (PixelType t);

		/** @brief Change the pixels value */
		void setPixels (Pixel** p);

		/** @brief Convert Image to string */
		string to_string ();

		/** @brief Set a pixel in a posicion */
		void setPixel (int r, int c, Pixel p);
};

#endif