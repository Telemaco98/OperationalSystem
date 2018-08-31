/**
 * @file	ManageImage.h
 * @brief 	Archive to declare the methods to manage the image
 *
 * @author 	Joaliton Luan (luanpereira00@outlook.com)
 * @author  Shirley Ohara (shirleyohara@ufrn.edu.br)
 * @since	13.11.2017
 * @data 	13.11.2017
 * @sa 		Image.h
 */
#ifndef MANAGEIMAGE_H_
#define MANAGEIMAGE_H_ value

#include <iostream>

#include "Image.h"

/**
 * @param im, imagem para ser processada e limiarizada.
 * @return imagem com os pixels limiarizados
 */
Image* limiarization(Image *im, Pixel limiar);

/**
 * @param img Imagem que será transformada
 * @param from, to parametros que marcam o tipo de tranformação. 
 *       1 = RGB, 2 = ybcr.
 * @return imagem no padrão especificado
 */
Image* transform(Image *im, PixelType from, PixelType to);

/**
 * @param dest a imagem a servir como base
 * @param src imagem a ser usada na operação de alfa
 * @return imagem resultante depois da operação de composição de alfa
 */
Image* alphaTransform(Image *dest, Image *src);

/**
 * @brief 	
 * @param 	img a imagem a servir como base
 * @param 	a imagem a ser usada na operação de alfa
 * @param 	imagem contendo os valores do filtro a ser usado na operaçao
 * @return 	imagem filtrada
 */
Image* filter(Image *dest, double filter[3][3]);

#endif