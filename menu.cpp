#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "BitmapHelper1.h"
#include "encoding.h"
# include "decoding.h"

using namespace std;
void encode();
void decoding();

int main() {
	char choice;
	cout << "Enter 'a' to encode a message, 'b' to decode a message, 'c' to exit program" << endl;
	cin >> choice;

	switch (choice)
	{
	case 'a': {
		cout << "encoding selected" << endl;
		encode();

		break;
	}
	case 'b': {
		cout << "decoding selected" << endl;
		decoding();
		break;
	}
	case 'c': {
		cout << "exit was selected" << endl;
		break;
	}
	}

	return 0;

}