#include <iostream>
using namespace std;

#include "File.h"
#include "Image.h"
#include "ManageImage.h"

int main(int argc, char **argv) {
    // read image
    Image* img = readImg("Original.ppm");

    // Pixel limiar;
    // limiar.rgb.R = 127;
    // limiar.rgb.G = 127;
    // limiar.rgb.B = 127;

    // Image* img2 = limiarization(img, limiar);
    // writeImg(img2, "Limirizada.ppm");

    // double **boxblur = NULL;
    // boxblur = new double*[3];
    // for (int j = 0; j < 3; j++) boxblur[j] = new double[j];
    
    Image* img2 = transform(img, PixelType::RGB, PixelType::YCbCr);
    writeImg(img2, "TransformYCbCr.ppm");

    double emboss[3][3] = {
        { -2, -1, 0 },
        { -1,  1,  1 },
        { 0, 1, 2 }
    };

    img2 = filter(img, emboss);
    writeImg(img2, "EmbossFilterYCbCr.ppm");


	return 0;
}