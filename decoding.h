#pragma once
#include "BitmapHelper1.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

double BinaryToDecimal(int revertedbinary[]);
void decoding();

void decoding() {
	int imageHeight = 0;  //define dimentions of image
	int imageWidth = 0;
	unsigned char*** imageData; //define array to store information about each pixel in image


	string namefile;
	cout << "Please enter name of file to decode" << endl;  //save input file name entered by user into a string called nameFile
	cin >> namefile;

	ReadBitmapImage(namefile.c_str(), imageData, imageWidth, imageHeight);
	//test if image entered is BMP format
	if (ReadBitmapImage(namefile.c_str(), imageData, imageWidth, imageHeight)) //function namefile.c_str() converts string namefile into pointer to char array
		cout << "file opening successful" << endl;
	else
		exit(-1);

	int binary[bitperbyte];   // this array stores 8 bits 
	int n = 0;       // index indicating element of binary

	char character; // once binary has 8 bits they will be converted into character and stored in this variable


	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			for (int channel = 0; channel < channelsperpointer; channel++) {   //"for each element of ImageData"
				int lsbpixel;
				lsbpixel = (imageData[i][j][channel] >> 0) & 1U; //stores lsb in lsbpixel
				binary[n] = lsbpixel;							//stores lsb into element number n of binary array
				if (n < (bitperbyte-1)) {                                   //if element of binary is not the seventh 
					n++;										//increment n
					continue;                                    //repeat
				}
				else if (n == (bitperbyte-1)) {    //if bits for the whole character are stored
					int ascii;
					ascii = BinaryToDecimal(binary);   //convert binary notation of character into its decimal which is the character's ascii code         
					if (ascii == 0 || (ascii < 1))  // ascii code for \0
						break;
					if (i > 1)  //if program not able to break code through line 51, output limited by shortening number of iteration                        
						break;
					character = (char)ascii;	  // cast character ascii code to character                                                
					cout << character;           // print the character
					n = 0;                        // set index of array binary to 0 so that binary is rewritten and process restarts
				}
			}
		}
	}
	ReleaseMemory(imageData, imageHeight, imageWidth); // call release image data memory allocated dynamically
}
double BinaryToDecimal(int revertedbinary[]) {   //given a 1d array of reverted binary of character, finds character's ascii code
	double decimal = 0;
	int factor = 0;
	for (int j = 0; j < bitperbyte; j++) {	//takes each bit and multiplies it by 2^bit's position
		factor = pow(2, j);
		decimal += revertedbinary[j] * pow(2, j);   // sums of multiplied bits
	}
	return (decimal);

}