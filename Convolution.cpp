#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad) {

    kernelHeight = kh;
    kernelWidth = kw;
    stride = stride_val;
    padding = pad;


    kernel = new double * [kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];
        for (int j = 0; j < kw; ++j) {
            kernel[i][j] = customKernel[i][j];

        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {

            delete[] kernel[i];
        }

    delete[] kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){

    // Deallocate old memory
    for (int i = 0; i < kernelHeight; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;

    // Copy from other
    kernelHeight = other.getKernelHeight();
    kernelWidth = other.getKernelWidth();
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.getKernel()[i][j];
        }
    }

}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; // self-assignment check
    }

    // Deallocate old memory
    for (int i = 0; i < kernelHeight; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;

    // Copy from other
    kernelHeight = other.getKernelHeight();
    kernelWidth = other.getKernelWidth();
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.getKernel()[i][j];
        }
    }

    return *this;





}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {

    double convolute = 0.0; // This holds the convolution results for an index.
    int x, y; // Used for input matrix index



    int outputHeight = (((input_image.get_height() - kernelHeight + 2 * padding) / stride) + 1);
    int outputWidth = (((input_image.get_width() - kernelWidth + 2 * padding) / stride) + 1);

    ImageMatrix output_image(outputWidth, outputHeight);

/*    double **returnArr = new double *[outputHeight];


    for (int i = 0; i < outputHeight; ++i) {
        returnArr[i] = new double[outputWidth];

    } */

    if (padding) {
//----------------------------- zero_Padding


        int paddedRows = input_image.get_height() + 2 * padding;
        int paddedCols = input_image.get_width() + 2 * padding;

        int** paddedArray = new int*[paddedRows];
        for (int i = 0; i < paddedRows; ++i) {
            paddedArray[i] = new int[paddedCols];
        }
        // Initialize the padded array with zeros
        for (int i = 0; i < paddedRows; ++i) {
            for (int j = 0; j < paddedCols; ++j) {
                paddedArray[i][j] = 0;
            }
        }

        // Copy the original array into the padded array
        for (int i = 0; i < input_image.get_height(); ++i) {
            for (int j = 0; j < input_image.get_width(); ++j) {

                // ?? get data şu şekil kullanılır mı?
                paddedArray[i + padding][j + padding] = input_image.get_data(i,j);
            }
        }
//------------------------------convolving the padded image

        // Fill output matrix: rows and columns are i and j respectively
        for (int i = 0; i < outputHeight; i++)

            for (int j = 0; j < outputWidth; j++) {
                x = i * stride; // Calculate the correct starting row index
                y = j * stride; // Calculate the correct starting column index

                // Kernel rows and columns are k and l respectively
                for (int k = 0; k < kernelHeight; k++) {
                    for (int l = 0; l < kernelWidth; l++) {
                        // Convolute here.
                        convolute += kernel[k][l] * paddedArray[x][y];
                        y++; // Move right.
                    }
                    x++; // Move down.
                    y = j; // Restart column position
                }
                output_image.get_data()[i][j] = convolute; // Add result to the output matrix.

//               returnArr[i][j] = convolute; // Add result to output matrix.

                convolute = 0.0; // Needed before we move on to the next index.
            }




    }
    else {

//-------------------------- convolving without padding.


        // Fill output matrix: rows and columns are i and j respectively
        for (int i = 0; i < outputHeight; i++)

            for (int j = 0; j < outputWidth; j++) {
                x = i * stride; // Calculate the correct starting row index
                y = j * stride; // Calculate the correct starting column index

                // Kernel rows and columns are k and l respectively
                for (int k = 0; k < kernelHeight; k++) {
                    for (int l = 0; l < kernelWidth; l++) {
                        // Convolute here.
                        convolute += kernel[k][l] * input_image.get_data()[x][y];
                        y++; // Move right.
                    }
                    x++; // Move down.
                    y = j; // Restart column position
                }
                output_image.get_data()[i][j] = convolute; // Add result to the output matrix.

//               returnArr[i][j] = convolute; // Add result to output matrix.

                convolute = 0; // Needed before we move on to the next index.
            }
        }

    return output_image;

    }


double **Convolution::getKernel() const {
    return kernel;
}

void Convolution::setKernel(double **kernel) {
    Convolution::kernel = kernel;
}

int Convolution::getKernelHeight() const {
    return kernelHeight;
}

void Convolution::setKernelHeight(int kernelHeight) {
    Convolution::kernelHeight = kernelHeight;
}

int Convolution::getKernelWidth() const {
    return kernelWidth;
}

void Convolution::setKernelWidth(int kernelWidth) {
    Convolution::kernelWidth = kernelWidth;
}
