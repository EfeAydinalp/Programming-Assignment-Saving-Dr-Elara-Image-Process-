# BBM 203 - Programming Assignment 1: Saving Dr. Elara

## Overview

This project is part of the BBM 203 Software Laboratory I course and revolves around basic image processing tasks using C++. The assignment involves manipulating matrices representing grayscale images and performing various operations such as convolution, edge detection, and image sharpening. The end goal is to decode and encode hidden messages in an image, simulating the process of uncovering secrets in a "Celestial Tapestry."

## Project Structure

- `ImageLoader.h/cpp`: Handles the loading of images into matrices.
- `ImageMatrix.h/cpp`: Manages image matrices and provides functions for matrix manipulation.
- `Convolution.h/cpp`: Implements convolution operations on image matrices.
- `ImageSharpening.h/cpp`: Provides functionality to sharpen images using convolution and basic arithmetic operations.
- `EdgeDetector.h/cpp`: Implements edge detection using the Sobel operator.
- `DecodeMessage.h/cpp`: Decodes hidden messages embedded in the image edges.
- `EncodeMessage.h/cpp`: Encodes messages into the image by modifying pixel values.

## Key Concepts

### 1. Convolution
Convolution is used to blend an image with a filter (kernel) to modify its appearance, such as blurring or sharpening the image.

### 2. Sobel Operator
A technique for edge detection by calculating the gradient magnitude of an image, identifying areas with high intensity changes.

### 3. Image Sharpening
Enhances the clarity of an image by emphasizing edges using a combination of original and blurred images.

### 4. Edge Detection
Detects edges in an image by calculating the gradient magnitude and applying a threshold to identify significant intensity changes.

## How to Run

1. Clone this repository:
   ```sh
   git clone https://github.com/EfeAydinalp/SavingDrElara-ImageProcess

2. Navigate to the project directory:
 ```sh
   cd SavingDrElara-ImageProcess
```
3. Compile the code using a C++ compiler:
 ```sh
   g++ -std=c++11 -o ImageProcessor main.cpp ImageLoader.cpp ImageMatrix.cpp Convolution.cpp ImageSharpening.cpp EdgeDetector.cpp DecodeMessage.cpp EncodeMessage.cpp

```
4. Run the executable:
 ```sh
   ./ImageProcessor input_image.pgm

```
Replace input_image.pgm with the path to your image file.


5. Follow the prompts to decode or encode messages in the image.

### INSTRUCTIONS.txt
```text
BBM 203 - Programming Assignment 1: Saving Dr. Elara

INSTRUCTIONS

1. **Introduction**
   - This assignment involves working with images represented as matrices and performing various image processing tasks, including convolution, sharpening, and edge detection. The final goal is to decode hidden messages in an image and encode responses.

2. **Setup**
   - Ensure you have a C++11 compatible compiler installed.
   - Clone the repository containing the code.
   - Compile the code as instructed in the README file.

3. **Code Overview**
   - `ImageLoader`: Loads images into matrices for processing.
   - `ImageMatrix`: Manages the matrices, including operations like convolution and edge detection.
   - `Convolution`: Applies filters to images using the convolution operation.
   - `ImageSharpening`: Sharpens the image by enhancing edges.
   - `EdgeDetector`: Detects edges in the image using the Sobel operator.
   - `DecodeMessage`: Decodes messages hidden in the image's edges.
   - `EncodeMessage`: Encodes a new message by modifying the image matrix.

4. **Tasks**
   - **Task 1**: Process an image to restore clarity, trace pathways, and decode a hidden message.
   - **Task 2**: Reformulate and embed a response message back into the image.

5. **Running the Program**
   - Follow the instructions in the README file to compile and run the program.
   - The program will prompt you to choose whether to decode or encode a message.
.



