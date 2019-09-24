#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

using namespace std;

int main() {
	int radius = 0;
	double perimeter = 0;
	double area = 0;
	double surfaceArea = 0;
	double volume = 0;
	double radius1 = 0;


	// ask for the radius from the user
	cout << "Please enter the radius of the circle (in whole inches only): " << flush;
	cin >> radius;

	// determine if the value entered was negative, if true, calculate the abs
	if (radius < 0) {
		radius = abs(radius);
		cout << "\nYou entered a negative value, but we will pretend you" <<
			" entered the absolute value, which would be: " << radius <<
			" inches." << endl;
	}
	else {
		cout << "\nYou entered " << radius << " inches for the radius" << endl;
	}


	// find the perimeter of the sphere in inches
	perimeter = 2 * M_PI * radius;

	// find the area of the circle in inches^2
	area = M_PI * pow(static_cast<double>(radius), 2.0);
	
	// find the surface area of the sphere in inches^2
	surfaceArea = 4 * M_PI * pow(static_cast<double>(radius), 2.0);
	
	// find the volume of the sphere inches^3
	volume = (4.0 / 3.0) * (M_PI * pow(static_cast<double>(radius), 3.0));
	
	// print the information in imperial unit (inches)
	cout << fixed << setprecision(3) << "Using the radius " << radius << " inches" <<
		"\nThe value of the perimeter of the circle is: " << perimeter <<
		" inches" << "\nThe value of the Area of the circle is: " << area <<
		" square inches" << "\nThe value of the surface area is: " <<
		surfaceArea << " square inches" << "\nThe value of the volume of the" <<
		" sphere is: " << volume << " cubic inches\n" << endl;

	// convert radius into centimeters
	radius1 = 2.54 * static_cast<double>(radius);
	cout << "Your radius in centimeters is " << radius1 << endl;

	// find the perimeter of the circle in cm
	perimeter = 2 * M_PI * (radius1);

	// find the area of the circle in cm^2
	area = M_PI * pow(radius1, 2.0);

	// find the surface area of the sphere in cm^2
	surfaceArea = 4 * M_PI * pow(radius1, 2.0);

	// find the volume of the sphere in cm^3
	volume = (4.0 / 3.0) * (M_PI * pow(radius1, 3.0));

	// print the information in standard units (inches)
	cout << fixed << setprecision(3) <<
		"\nThe value of the perimeter of the circle is: " << perimeter <<
		" centimeters" << "\nThe value of the Area of the circle is: " << area <<
		" square centimeters" << "\nThe value of the surface area is: " <<
		surfaceArea << " square centimeters" << "\nThe value of the volume of the" <<
		" sphere is: " << volume << " cubic centimeters\n" << endl;

	char dummy = 'a';
	cin >> dummy;

	return 0;
}