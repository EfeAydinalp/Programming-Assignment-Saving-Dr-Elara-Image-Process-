#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <utility>
#include <cmath>

#include "ImageLoader.h"
#include "ImageMatrix.h"
#include "Convolution.h"

#include "ImageLoader.cpp"
#include "ImageSharpening.h"
#include "ImageMatrix.cpp"
#include "Convolution.cpp"

#include "ImageSharpening.cpp"



using namespace std;



// Global img, bad practice :(

// define a 5x5 matrix to initialize a 5x5 image
const double* directData1[5] = {
        new double[5]{1.0, 2.0, 3.0, 4.0, 5.0},
        new double[5]{6.0, 7.0, 8.0, 9.0, 10.0},
        new double[5]{11.0, 12.0, 13.0, 14.0, 15.0},
        new double[5]{16.0, 17.0, 18.0, 19.0, 20.0},
        new double[5]{21.0, 22.0, 23.0, 24.0, 25.0}
};



// create an iamge
ImageMatrix image1(directData1, 5, 5);


void compare_images(const ImageMatrix& im1, const ImageMatrix& im2, double& score, int& total_number){
    for (int i = 0; i < im1.get_height(); i++) {
        for (int j = 0; j < im1.get_width(); j++) {
            total_number++;
            double im1_value = std::round(im1.get_data()[i][j] * 1e3) / 1e3;  // rounding to 3 decimal places
            double im2_value = std::round(im2.get_data()[i][j] * 1e3) / 1e3;  // rounding to 3 decimal places
            if (im1_value == im2_value) {
                score += 1.0;
            }
            else{
                cout << "im1_value: " << im1_value << " expected: " << im2_value << " at " << i << "," << j <<endl;

            }
        }
    }
}

void test_conv(double& score, int& total_number){

    //  3x3 Gaussian kernel, stride 1, no padding
    double* kernel_gaussian[3] = {
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0}
    };


    // TEST 1
    // conv obj1: 3x3 kernel, stride 1, no padding
    Convolution conv_gaussian_s1_no_pad(kernel_gaussian, 3, 3, 1, false);

    // convolve the image with the kernel
    ImageMatrix convolved_image1 = conv_gaussian_s1_no_pad.convolve(image1);

    // The expected data 3x3
    const double* directData2[3] = {
            new double[3]{7, 8, 9},
            new double[3]{12, 13, 14},
            new double[3]{17, 18, 19}
    };

    // create an image
    ImageMatrix expected_image(directData2, 3, 3);

    // compare the convolved image with the expected image
    compare_images(convolved_image1, expected_image, score, total_number);


    // TEST 2
    // conv obj2: 3x3 kernel, stride 1, with padding
    Convolution conv_gaussian_s1_with_pad(kernel_gaussian, 3, 3, 1, true);

    // convolve the image with the kernel
    ImageMatrix convolved_image2 = conv_gaussian_s1_with_pad.convolve(image1);

    // the expected data2:
    const double* expectedData2[5] = {
            new double[5]{1.77778, 3, 3.66667, 4.33333, 3.11111},
            new double[5]{4.33333, 7, 8, 9, 6.33333},
            new double[5]{7.66667, 12, 13, 14, 9.66667},
            new double[5]{11, 17, 18, 19, 13},
            new double[5]{8.44444, 13, 13.6667, 14.3333, 9.77778}
    };

    // create an image
    ImageMatrix expected_image2(expectedData2, 5, 5);

    // compare the convolved image with the expected image
    compare_images(convolved_image2, expected_image2, score, total_number);



}

void test_sharpening(double& score, int& total_number){
    // create an image sharpening object
    ImageSharpening imageSharpening;

    // sharpen the image
    ImageMatrix sharpened_image = imageSharpening.sharpen(image1, 2);

    // the expected data:
    const double* expectedData[5] = {
            new double[5]{0, 0, 1.66667, 3.33333, 8.77778 },
            new double[5]{9.33333, 7, 8, 9, 17.3333},
            new double[5]{17.6667, 12, 13, 14, 25.6667},
            new double[5]{26, 17, 18, 19, 34 },
            new double[5]{46.1111, 40, 41.6667, 43.3333, 55.4444}
    };

    // create an image
    ImageMatrix expected_image(expectedData, 5, 5);

    // compare the convolved image with the expected image
    compare_images(sharpened_image, expected_image, score, total_number);



}





int main() {
    double score = 0.0;
    int total_number = 0;

    // test convolution
    test_conv(score, total_number);

    // test sharpening
    test_sharpening(score, total_number);




    // print the score / total_number
    cout << "Score: " << score << " / " << total_number << endl;




    return 0;
}


// how to compile
// g++ -std=c++11 -o main main.cpp ImageMatrix.cpp Convolution.cpp DecodeMessage.cpp EncodeMessage.cpp ImageSharpening.cpp EdgeDetector.cpp ImageProcessor.cpp