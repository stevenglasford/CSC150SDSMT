#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

using namespace std;

// Function to calculate a factorial
long double factorial(int a) {
	long double factorial = a;
	for (int n = 1; n <= a; ++n) {
		factorial *= n;
	}
	return factorial;
}

// Function to convert degrees to radians within the specified period
double convertToRadians(double degrees) {
	double radians = 0;
	radians = ((degrees)*(M_PI / 180.0));
	return radians;
}

// Function to approximate e^x
double my_ex(double x, int numTerms) {
	double ex = 0;
	return ex;
}

// Function to approximate sin(x)
double my_sin(double x, int numTerms) {
	double sin = 0;
	return sin;
}

// Function to approximate cos(x)
double my_cos(double x, int numTerms) {
	double value = 0;
	return value;
}

// Prompt user and read number of terms to use. Repeat until they enter a 
//	valid value
int getNumTerms() {
	int terms = 0;
	cout << "How many terms do you want for the calculation? (0<=x<=5): " << flush;
	cin >> terms;
	return terms;
}

// Prompt user and read x in degrees. Repeat until they enter a valid value
double getDegrees() {
	double degrees = 0;
	return degrees;
}

// Function to print a selection menu and retrieve the user's choice
int getMenuChoice() {
	int choice;
	cout << "Please choose one of the following functions to approximate\n"
		<< "\n1.\te^x\n" << "2.\tsin(x)\n" << "3.\tcos(x)\n" <<
		"\n4.\tExit the program" << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "\nYou have chosen to approximate e^x" << endl;
		break;
	case 2:
		cout << "\nYou have chosen to approximate sin(x)" << endl;
		break;
	case 3:
		cout << "\nYou have chosen to approximate cos(x)" << endl;
		break;
	case 4:
		cout << "\nYou have chosen to exit the program. Goodbye..."
			<< endl;
		break;
	default:
		cout << "\nPlease enter a valid number" << endl;
		break;
	}
	return choice;
}



int main() {
	int choice = 0;

	do {
		choice = getMenuChoice();
	} while (choice != 4);

	return 0;
}