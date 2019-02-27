/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);

	/*===

	Insert Lab 2 code here:

	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation(s)
	3. Compute the inverse 2D FFT of the image
	4. For parts (b) and (c), re-normalize the image

	===*/
	int width = image.Width();
	int height = image.Height();
	double frequency = 0.1;

	//compute FFT for each row
	for (int i =0; i<height;i++){
			vector<Complex> signal;
			signal.resize (width);
			for (int j =0; j<width;j++){
				signal[j] = image.Pixel(j, i);
			}
			FFT::Transform (signal);

			for (int j =0; j<width;j++){
				image.Pixel(j, i) = signal[j];
			}
	}


	//compute FFT for each colomn
	for (int i =0; i<width;i++){
			vector<Complex> signal;
			signal.resize (height);
			for (int j =0; j<height;j++){
				signal[j] = image.Pixel(i, j);
			}
			FFT::Transform (signal);

			for (int j =0; j<height;j++){
				image.Pixel(i, j) = signal[j];
			}
	}
	int w = width;
	int h = height;
	for (int i=0; i < w; i++){
		for (int j =0; j < h; j++){
			//in fourier domain, keep four corner square with size (x_size*frequency)^2
			if( (i<=frequency*w && j<=frequency*h )|| (i>=w-frequency*w && j>= h-frequency*h)
				|| (i<=frequency*w && j>= h-frequency*h)|| (i>=w-frequency*w && j<= frequency*h))
				{}
			else {
				//set pixels in areas(outside cutoff frequency) other than the four corner squares to 0
				image.Pixel(i,j)=0;
			}
		}
	}


	//compute inverseFFT for each row
	for (int i =0; i<height;i++){
			vector<Complex> signal;
			signal.resize (width);
			for (int j =0; j<width;j++){
				signal[j] = image.Pixel(j, i);
			}
			FFT::InverseTransform (signal);

			for (int j =0; j<width;j++){
				image.Pixel(j ,i) = signal[j];
			}
	}






	//compute inverseFFT for each colomn
	for (int i =0; i<width;i++){
			vector<Complex> signal;
			signal.resize (height);
			for (int j =0; j<height;j++){
				signal[j] = image.Pixel(i,j);
			}
			FFT::InverseTransform (signal);

			for (int j =0; j<height;j++){
				image.Pixel(i, j) = signal[j];
			}
	}


	// save the image
	image.SavePng (argv[2]);

	return 0;
}
