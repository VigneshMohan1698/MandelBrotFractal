// FractalImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <complex>
#include <iostream>
#include "BitmapInfoHeader.h"
#include "MandelBrot.h"
#include "BitmapHeaderFile.h" 
#include "Bitmap.h"
#include <fstream>
#include <math.h>
#include <cstdint>
using namespace std;
int main()
{
	const int WIDTH = 800;
	const int HEIGHT = 600;
	Bitmap bitmap(WIDTH, HEIGHT);
	
	double min = 999999;
	double max = -999999;
	unique_ptr<int[]> histogram(new int[MandelBrot::MAX_ITERATIONS]{ 0 });
	unique_ptr<int[]> fractalColor(new int[WIDTH*HEIGHT]{ 0 });
	uint8_t color;
	for(int i = 0 ;i< HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			double xFractal = (j - WIDTH/2 -200) * 2.0 / HEIGHT;
			double yFractal = (i - HEIGHT/2) * 2.0 / HEIGHT;
			int iterations = MandelBrot::getIterations(xFractal, yFractal);
			fractalColor[i * WIDTH + j] = iterations;
			if (iterations < MandelBrot::MAX_ITERATIONS)
			{
				histogram[iterations]++;
			}		
			
		}
		
	int totalhistogram = 0;
	for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++)
	{
		totalhistogram += histogram[i];
	}

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			uint8_t red = 0;
			uint8_t blue = 0;
			uint8_t green = 0;
			int iterations = fractalColor[i * WIDTH + j];
			
			if(iterations < MandelBrot :: MAX_ITERATIONS)
			{
				double hue = 0.0;
				for (int i = 0; i <= iterations; i++)
				{
					hue += ((double)histogram[i] / totalhistogram);
				}
				red = pow(255, hue);
				/*cout << hue << endl;*/
			}
				
			/*color = (uint8_t)(255 * (double)iterations / MandelBrot::MAX_ITERATIONS);
			color = color * color * color;*/
			bitmap.setPixel(j, i, red, blue, green);
		}

	bitmap.write("FractalImage2.bmp");
	cout << "Finished" << endl;

}

