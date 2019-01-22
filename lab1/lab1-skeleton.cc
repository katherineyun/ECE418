/*===
lab1-skeleton.cc

Abstract: Skeleton for Lab 1
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int setAverage(Image& image, int row, int col){
	int sum = 0;
	for(int i = row; i<row+4; i++){
		for(int j = col; j<col+4;j++){
			sum+=image.Pixel(i,j);
		}
	}
	int average = sum/16;

	for(int i = row; i<row+4; i++){
		for(int j = col; j<col+4;j++){
			image.Pixel(i,j) = average;
		}
	}
}


int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 3)
	{
		cerr << "Usage: lab1 in.png out.png" << endl;
		return 1;
	}

	// load the image
	Image image;
	image.LoadPng (argv[1]);

	/*==

	Insert Lab 1 Code Here

	==*/

	for(int i = 0; i<image.Height()-4;i=i+4){
		for(int j = 0; j<image.Width()-4;j=j+4){
			setAverage(image,i,j);
			printf("%d %d\n",i,j);
		}
	}



	// save it
	image.SavePng (argv[2]);

	return 0;
}
