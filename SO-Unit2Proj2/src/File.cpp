#include <iostream>
using std::getline;
using std::endl;
using std::cout;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <string>
using std::string;

#include <cstdlib>
#include <cstdio>
using std::atoi;

#include "File.h"
#include "Image.h"

/**
 * @brief 	Take the image of the archive 
 * @param 	archiveName		The archive name
 * @return 	img 			The image read
 */
Image* readImg (string archiveName) {
	string way = "./image/", imgS, aux;
	imgS = way + archiveName;
	ifstream input;
	//cout << imgS;
	input.open(imgS.c_str());

	getline(input, aux);
	int row, col;
	input >> row >> col;
	getline(input, aux);
	Pixel** pixels = NULL;

	pixels = new Pixel*[row];
	for (int j = 0; j < col; j++) pixels[j] = new Pixel[col];

	for (int i = 0; i < row; i++) {	
		for (int j = 0; j < col; j++) {
			input >> pixels[i][j].rgb.R;
			input >> pixels[i][j].rgb.G;
			input >> pixels[i][j].rgb.B;
		}
	}
	input.close();

	Image* img = new Image(row, col, PixelType::RGB);
	img->setPixels(pixels);
	return img;
}

/**
 * @brief 	Write the image in a archive 
 * @param 	img 			The image
 * @param 	archiveName		The archive name
 */
void writeImg(Image* img, string archiveName) {
	string way = "./image/", imgS, aux;
	imgS = way + archiveName;
	ofstream output;
	output.clear();
	output.open(imgS.c_str());

	output << "P3" << endl;
	output << img->getWidth() << " " << img->getHeight() << endl;
	output << 255 << endl;

	Pixel** pixels = img->getPixels();
	
	for (int i = 0; i < img->getWidth(); i++) {	
		for (int j = 0; j < img->getHeight(); j++) {
			output << pixels[i][j].rgb.R << " ";
			output << pixels[i][j].rgb.G << " ";
			output << pixels[i][j].rgb.B;
			output << endl;
		}
	}
	output.close();
}

/**
 * @brief 	Convert a image in string 
 * @param 	immage 		The image string
 */
Image* from_string (string image) {
	int end, begin;

	end = image.find(" ", 0);
	string type = image.substr(0, end);
	PixelType pixelT;
	if(type == "rgb") pixelT = PixelType::RGB;
	else pixelT = PixelType::YCbCr;

	begin = end + 1;
	end = image.find(" ", end);
	string rowS = image.substr(begin, end);
	int row = atoi(rowS.c_str());

	begin = end + 1;
	end = image.find(" ", end);
	string colS = image.substr(begin, end);
	int col = atoi(colS.c_str());

	Image* img = new Image(row, col, pixelT);

	if(pixelT == PixelType::RGB) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				Pixel pixel;

				begin = end + 1;
				end = image.find(" ", end);
				string redS = image.substr(begin, end);
				int red = atoi(redS.c_str());

				begin = end + 1;
				end = image.find(" ", end);
				string greenS = image.substr(begin, end);
				int green = atoi(greenS.c_str());

				begin = end + 1;
				end = image.find(" ", end);
				string blueS = image.substr(begin, end);
				int blue = atoi(blueS.c_str());

				pixel.rgb.R = red;
				pixel.rgb.G = green;
				pixel.rgb.B = blue;

				img->setPixel(i, j, pixel);
			}
		}
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				Pixel pixel;

				begin = end + 1;
				end = image.find(" ", end);
				string yS = image.substr(begin, end);
				int Y = atoi(yS.c_str());

				begin = end + 1;
				end = image.find(" ", end);
				string cbS = image.substr(begin, end);
				int Cb = atoi(cbS.c_str());

				begin = end + 1;
				end = image.find(" ", end);
				string crS = image.substr(begin, end);
				int Cr = atoi(crS.c_str());

				pixel.ycbcr.Y = Y;
				pixel.ycbcr.Cb = Cb;
				pixel.ycbcr.Cr = Cr;

				img->setPixel(i, j, pixel);
			}
		}
	}

	return img;
}