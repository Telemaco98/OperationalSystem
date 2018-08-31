/**
 * @file	ManageImage.h
 * @brief 	Archive to implements the methods to manage the image
 *
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	13.11.2017
 * @data 	13.11.2017
 * @sa 		Image.h
 */

#include <iostream>
using std::cout;
using std::endl;

#include "ManageImage.h"
#include "Image.h"

/**
 * @param 	im, imagem para ser processada e limiarizada.
 * @return 	imagem com os pixeis limiarizados
 */
Image* limiarization(Image *im, Pixel limiar) {
	Image* exit = im;
	Pixel** origin = im->getPixels ();
	int mediaLimiar = (limiar.rgb.R + limiar.rgb.G + limiar.rgb.B)/3;

	if(im->getType() == PixelType::RGB) {
    	for (int row = 0; row < im->getWidth() ; row++) {
        	for (int col = 0; col < im->getHeight() ; col++) {
				int media = (origin[row][col].rgb.R + origin[row][col].rgb.G + origin[row][col].rgb.B)/3;

				if(media > mediaLimiar){
					origin[row][col].rgb.R = 255;
					origin[row][col].rgb.G = 255;
					origin[row][col].rgb.B = 255;
				}
				else{
					origin[row][col].rgb.R = 0;
					origin[row][col].rgb.G = 0;
					origin[row][col].rgb.B = 0;
				}
			}
		}
	} else {
		mediaLimiar = (limiar.ycbcr.Y + limiar.ycbcr.Cb + limiar.ycbcr.Cr)/3;

		for (int row = 0; row < im->getWidth() ; row++) {
        	for (int col = 0; col < im->getHeight() ; col++) {
	        	int media = (origin[row][col].ycbcr.Y + origin[row][col].ycbcr.Cb + origin[row][col].ycbcr.Cr)/3;

				if(media > mediaLimiar){
					origin[row][col].ycbcr.Y  = 255;
					origin[row][col].ycbcr.Cb = 255;
					origin[row][col].ycbcr.Cr = 255;
				}
				else{
					origin[row][col].ycbcr.Y  = 0;
					origin[row][col].ycbcr.Cb = 0;
					origin[row][col].ycbcr.Cr = 0;
				}
	        }
	    }
	}

    exit->setPixels(origin);
    return exit;
}

/**
 * @param img Imagem que será transformada
 * @param from, to parametros que marcam o tipo de tranformação. 
 *       1 = RGB, 2 = ycbcr.
 * @return imagem no padrão especificado
 */
Image* transform(Image *im, PixelType from, PixelType to) {
	if (from == to) return im;

	Image* exit = im;
	Pixel** origin = im->getPixels();
	
	if (from == PixelType::RGB) { // change to ycbcr
		for (int row = 0; row < im->getWidth() ; row++) {
        	for (int col = 0; col < im->getHeight() ; col++) {
        		origin[row][col].ycbcr.Y  = (int) (16 + (65.738 * origin[row][col].rgb.R)/256 + (129.057 * origin[row][col].rgb.G)/256 + (25.064 * origin[row][col].rgb.B)/256);
        		origin[row][col].ycbcr.Cb = (int) (128 - (37.945 * origin[row][col].rgb.R)/256 - (74.494 * origin[row][col].rgb.G)/256 + (112.439 * origin[row][col].rgb.B)/256);
        		origin[row][col].ycbcr.Cr = (int) (128 + (112.439 * origin[row][col].rgb.R)/256 - (94.154 * origin[row][col].rgb.G)/256 - (18.285 * origin[row][col].rgb.B)/256);
        		origin[row][col].ycbcr.a  = origin[row][col].rgb.a;
	        }
	    }

	} else { //change to RGB
		for (int row = 0; row < im->getWidth() ; row++) {
        	for (int col = 0; col < im->getHeight() ; col++) {
				origin[row][col].rgb.R = (int) (origin[row][col].ycbcr.Y + 1.402 * (origin[row][col].ycbcr.Cr - 128));
				origin[row][col].rgb.G = (int) (origin[row][col].ycbcr.Y - 0.34414 * (origin[row][col].ycbcr.Cb - 128) - 0.71414 * ( origin[row][col].ycbcr.Cr - 128));
				origin[row][col].rgb.B = (int) (origin[row][col].ycbcr.Y + 1.772 * (origin[row][col].ycbcr.Cb - 128));
				origin[row][col].rgb.a = origin[row][col].ycbcr.a;
        	}
    	}
	}

	exit->setType(to);
	return exit;
}

/**
 * @param 	dest 	a imagem a servir como base (background)
 * @param 	src 	imagem a ser usada na operação de alfa
 * @return 	exit 	resultante depois da operação de composição de alfa
 */
Image* alphaTransform(Image *dest, Image *src) {
	if (dest->getHeight() == src->getHeight() and dest->getWidth() == src->getWidth() and dest->getType() == src->getType()) {
		Image* exit = dest;

		Pixel** background = dest->getPixels();
		Pixel** foreground = src->getPixels();
		Pixel** result = exit->getPixels();

		for (int row = 0; row < dest->getWidth() ; row++) {
	    	for (int col = 0; col < dest->getHeight() ; col++) {
				if(dest->getType() == PixelType::RGB) {
					double a1 = background[col][row].rgb.a / 255.0;
				    double a2 = foreground[col][row].rgb.a / 255.0;

				    result[row][col].rgb.R = (int) (a1 * background[col][row].rgb.R + a2 * (1 - a1) * foreground[col][row].rgb.R);
				    result[row][col].rgb.G = (int) (a1 * background[col][row].rgb.G + a2 * (1 - a1) * foreground[col][row].rgb.G);
				    result[row][col].rgb.B = (int) (a1 * background[col][row].rgb.B + a2 * (1 - a1) * foreground[col][row].rgb.B);
				    result[row][col].rgb.a = (int) (255 * (a1 + a2 * (1 - a1)));
				} else {
		    		double a1 = background[col][row].ycbcr.a / 255.0;
				    double a2 = foreground[col][row].ycbcr.a / 255.0;

				    result[row][col].ycbcr.Y  = (int) (a1 * background[col][row].ycbcr.Y + a2 * (1 - a1) * foreground[col][row].ycbcr.Y);
				    result[row][col].ycbcr.Cb = (int) (a1 * background[col][row].ycbcr.Cb + a2 * (1 - a1) * foreground[col][row].ycbcr.Cb);
				    result[row][col].ycbcr.Cr = (int) (a1 * background[col][row].ycbcr.Cr + a2 * (1 - a1) * foreground[col][row].ycbcr.Cr);
				    result[row][col].ycbcr.a  = (int) (255 * (a1 + a2 * (1 - a1)));
		    	}
	    	}
		}

	    exit->setPixels(result);
	    return exit;
	} else return NULL;
}
// referência: https://stackoverflow.com/questions/5149722/get-pixel-color-after-alpha-blend

/**
 * @param 	dest 	a imagem a servir como base
 * @param 	filter 	imagem contendo os valores do filtro a ser usado na operaçao
 * @return 	imagem 	filtrada
 */
Image* filter(Image *dest, double filter[3][3]) { //FIXME
	Image* exit = dest;
	Pixel** origin = dest->getPixels();
	
	for (int row = 1; row < dest->getWidth() - 1; row++) {
		for (int col = 1; col < dest->getHeight() -1; col++) {
			
			if (dest->getType() == PixelType::RGB) { 
				int sumR = 0, sumG = 0, sumB = 0;
				for(int i = 0; i < 3; i++){
					for(int j = 0; j < 3; j++){
						sumR += (origin[row-1 + i][col-1 + j].rgb.R) * filter[i][j];
						sumG += (origin[row-1 + i][col-1 + j].rgb.G) * filter[i][j];
						sumB += (origin[row-1 + i][col-1 + j].rgb.B) * filter[i][j];
					}
				}

				if(sumR > 255) sumR = 255;
				if(sumG > 255) sumG = 255;
				if(sumB > 255) sumB = 255;
				if(sumR < 0) sumR = 0;
				if(sumG < 0) sumG = 0;
				if(sumB < 0) sumB = 0;

				origin[row][col].rgb.R = sumR;
				origin[row][col].rgb.G = sumG;
				origin[row][col].rgb.B = sumB;

			} else {
				int sumY = 0, sumCb = 0, sumCr = 0;
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						sumY  += (origin[row-1 + i][col-1 + j].ycbcr.Y) * filter[i][j];
						sumCb += (origin[row-1 + i][col-1 + j].ycbcr.Cb) * filter[i][j];
						sumCr += (origin[row-1 + i][col-1 + j].ycbcr.Cr) * filter[i][j];
					}
				}

				if(sumY > 255) sumY = 255;
				if(sumCb > 255) sumCb = 255;
				if(sumCr > 255) sumCr = 255;
				if(sumY < 0) sumY = 0;
				if(sumCb < 0) sumCb = 0;
				if(sumCr < 0) sumCr = 0;

				origin[row][col].ycbcr.Y = sumY;
				origin[row][col].ycbcr.Cb = sumCb;
				origin[row][col].ycbcr.Cr = sumCr;
			}
		}
	}
	exit->setPixels(origin);
	return exit;
}