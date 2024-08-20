#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){



}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    double* kernel_gaussian[3] = {
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0}
    };

    Convolution convolution(kernel_gaussian,3,3,1, true);
    ImageMatrix blurred_image = convolution.convolve(input_image);

    // Calculate the sharp image using the formula

    ImageMatrix sharp_image(3,3);

    sharp_image = input_image-blurred_image;

    sharp_image = sharp_image*k;

    sharp_image = sharp_image + input_image;


// Clip values less than 0 to 0 and greater than 255 to 255
    for (int i = 0; i < sharp_image.get_height(); i++) {
        for (int j = 0; j < sharp_image.get_width(); j++) {
            double value = sharp_image.get_data(i, j);
            if (value < 0) {
                sharp_image.setData(i,j,0);
            } else if (value > 255) {
                sharp_image.setData(i,j,255);
            }
        }
    }


    return sharp_image;
}





