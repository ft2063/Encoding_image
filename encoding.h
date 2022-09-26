#pragma once
#include "BitmapHelper1.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

void DecimalToBinary(int n, int binary[]);
void RevertBinary(int binary[], int revertedbinary[]);
void encode();

const int bitperbyte = 8;
const int messagelength = 50;
const int channelsperpointer = 3;
using namespace std;

void DecimalToBinary(int n, int binary[]) {   //given number in decimal n<256, finds n in binary, stores each bit as element of binary[]
	for (int i = bitperbyte - 1; n > 0; i--)
	{
		binary[i] = n % 2;
		n = n / 2;
	}
	for (int j = 0; j < bitperbyte; j++) {
		if (binary[j] != 1)
			binary[j] = 0;
	}
}
void RevertBinary(int binary[], int revertedbinary[]) {  //reverts binary by sorting in reverse order elements of  binary[]
	for (int a = 0; a < bitperbyte; a++) {
		revertedbinary[a] = binary[(bitperbyte-1) - a];
	}

}
void encode (){
	int imageHeight = 0, imageWidth = 0;
	unsigned char*** imageData;

	string namefile;
	cout << "Please enter name of file to encode" << endl;  //save input file name entered by user into a string called nameFile
	cin >> namefile;

	ReadBitmapImage(namefile.c_str(), imageData, imageWidth, imageHeight);
	//test if image entered is BMP format
	if (ReadBitmapImage(namefile.c_str(), imageData, imageWidth, imageHeight)) //function namefile.c_str() converts string namefile into pointer to char array
		cout << "file opening successful" << endl;
	else 
		exit (-1);
	
	cin.ignore();
	string secretmessage;
	const char* secretmessagearray;
	cout << "please enter the secret message to be encoded "<<endl;
	getline(cin, secretmessage);
	secretmessage += "\0";
	secretmessagearray = secretmessage.c_str();  //secret message string is converted in array of characters

	int messagetable[messagelength * bitperbyte];		//1d statically allocated array messagetable stores bits for each letter of the secret message
	int* messagetablePtr;								// pointer messagetablePtr grants access to elements of messagetable
	messagetablePtr = messagetable;

	for (int i = 0; secretmessagearray[i] != '\0'; i++) {
		int asciicharacter;
		asciicharacter = (int)secretmessagearray[i];			//convert letter i of secret message in its ascii code
		int binary[bitperbyte];
		DecimalToBinary(asciicharacter, binary);				//convert each letter from ascii to binary, stores bits in array
		int revertedbinary[bitperbyte];
		RevertBinary(binary, revertedbinary);
		for (int j = 0; j < bitperbyte; j++) {							//storing reverted binary for each letter in messagetable
			*messagetablePtr = revertedbinary[j];
			messagetablePtr++;
		}
	}
	messagetablePtr = messagetable;									//reset pointer messagetablePtr to first element of messagetable

	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			for (int channel = 0; channel < channelsperpointer; channel++) {
				int lsbpixel;
				lsbpixel = (imageData[i][j][channel] >> 0) & 1U; //compare lsb of each element in imageData with each element of messagetable (bites of each character)
				if (lsbpixel != *messagetablePtr)
					imageData[i][j][channel] ^= 1UL << 0;     //substitue lsb of element in imageData with Msb of character if they differ
				if (*messagetablePtr != 0 && *messagetablePtr != 1)
					break;
				messagetablePtr++;
			}
		}
	}


	WriteBitmapImage(namefile.c_str(), imageData, imageWidth, imageHeight); // call WriteBitmapImage to modify bitmap image 
	ReleaseMemory(imageData, imageHeight, imageWidth);						//call releaseMemory to release memory allocated dinamically
}