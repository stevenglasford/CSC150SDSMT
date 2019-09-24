/*************************************************************************//**
 * @file prog2.cpp
 *
 * @mainpage Program 2 -
 *
 * @section CSC-150-M001 Computer Science 1
 *
 * @author Steven Glasford
 *
 * @date 10-10-2017
 *
 * @par Professor:
 *			Dr. Pyeatt
 *
 * @par Course:
 *			CSC-150-M001, 10 AM
 *
 * @par Location:
 *			McLaury - 306
 *
 * @section program_section Program Information
 *
 * @details This program uses Taylor series expansion/approximation to 
 * try to see if approximation is truly faster than actually calculating the 
 * the function using the standard math functions inside the standard libraries,
 * then the program outputs a funny looking thing when you exit
 *
 * @par Compiling Instructions:
 *		I used Visual Studio Community 2017 to compile this program
 *
 *	@par Usage:
	@verbatim
	c:\> prog2.exe
	d:\> c:\bin\prog2.exe
	@endverbatim
 *
 *	@section todo_bugs_modification_section To do, Bugs, and Modifications
 *
 * 	@bug Doxygen will not produce documentation for sleepy(), stars(), space(),
 * desert(), obamaWebsite(), or exitDialog() even though the correct structures
 * are in place
 *
 *	@par Modifications and Development Time line:
	@verbatim
	Date			Modification
	-------------   ----------------------------------------------------------
	9/19/2017		I finished most of the program within two hours between
					7:00P and 9:00P
	9/20/2017		I added the cool ASCII art exit functions
	9/24/2017		I changed the naming rules inside this program
					(FunctionFunction, variableVariable)
	9/24/2017		I added the ability to see how long each calculation took
					in nanoseconds
	9/29/2017		I added the functions ClockBegin(), ClockEnd(), 
					Duration(), TimeAverage(); as well as added the timeArray
					for calculating the average time
	10/1/2017		I finished the documentation and commenting 
					(functionFunction, variableVariable)
	10/3/2017		I removed function clockTime()
	@endverbatim
*
*****************************************************************************/

#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <chrono>
#include <ratio>
#include <thread>

using namespace std;

/*!
 * @brief timeLoops is a constant integer, and allows for changing the 
 * number of times the average time loop runs much easier than otherwise
 */
//This constant integer is used for calculating the average time it took
//to run a calculation
const int TIME_LOOPS = 100000;
/*!
* @brief timeArray[] temporarily stores a bunch of duration values
* and is used in the calculation of the average time in timeAverage()
*/
int timeArray[TIME_LOOPS];
/*!
* @brief temp is just a general purpose temporary variable, mostly
* used in the approximation calculations
*/
double temp = 0;
/*!
* @brief choice is the value entered by the user after being presented
* the menu options, a 4 exits the program, and thing else makes the 
* program enter a series of rather complex loops and functions
*/
int choice = 0;
/*!
* @brief xxx is the value of the input for the e^x approximation
* and actual calculations
*/
double xxx = 0;
/*!
* @brief degrees is the value inputted by the user for the trig calculations
* which is eventually converted into radians
*/
double degrees = 0;
/*!
* @brief radians is the value of radians from the previous variable degrees
*/
double radians = 0;
/*!
* @brief terms acts as the level of approximation, and is used only in the 
* the approximation calculations, it is always an integer. The higher the value
* the more accurate the calculation
*/
int terms = 0;
/*!
* @brief actual is the actually calculated value from the given inputs using
* the standard libraries
*/
double actual = 0;
/*!
* @brief approx is the approximated value using the approximation functions
* I created for this assignment
*/
double approx = 0;
/*!
* @brief carryOn acts almost like an anti-tripping variable, in that if it is
* tripped or switched to the true statement, then instead of ending the 
* program or going into a loop, rather the program will advance, otherwise 
* the program will continue through the loop
*/
bool carryOn = false;
//the rest of these are just prototypes, the documentation for these are
// with the definitions
void introduction();
void wait();
long double factorial( int a );
double convertToRadians( double degrees );
double myX( double x, int numTerms );
double mySin( double x, int numTerms );
double myCos( double x, int numTerms );
int getNumTerms();
double getX();
double getDegrees();
void menuList();
int duration( chrono::high_resolution_clock::time_point begin,
	chrono::high_resolution_clock::time_point end );
int timeAverage();
void xDeal();
void trigTerms( int& terms, double& degrees );
int clockRadians( double degrees );
void sineDeal();
void cosineDeal();
int getMenuChoice();
void plane();
void truck();
void sleepy();
void stars();
void space();
void desert();
void obamaWebsite();
void exitDialog();

/**************************************************************************//** 
 * @author		Steven Glasford
 * 
 * @par Description: 
 * This is the main function, and it puts everything together
 * 
 * @param[in]		choice		This is the choice entered by the user
 * 
 * @returns			0			There is only one possible way that this 
 *								program can end, which is if the user enters
 *								the number 4 for the menu dialog, otherwise
 *								it will simply loop forever
 * 
 *****************************************************************************/
int main() {
	int choice = 0;
	//This will introduce the user to the program, and will produce the 
	//menus
	introduction();

	//Program successfully exits if the user enters a 4 in the first menu
	do {
		//As long as choice is not 4, the loop will be continuous
		choice = getMenuChoice();
	} while (choice != 4);

	//This will produce the cool ASCII art on exit
	exitDialog();
	//This pauses the screen so the program doesn't simply exit when you 
	//tell it to. It ensures that the user can take a moment to gaze
	//upon the awesome ASCII art at the end
	system("pause");
	return 0;

}

/**************************************************************************//**
* @author Steven Glasford
*
* @par Description:
* This function is to introduce the user to the program
*
* @return void
*
*****************************************************************************/
void introduction() {
	//This is a short introduction to the program itself
	cout << "This program uses Taylor and Mclaurin series to " <<
		"approximate the values of an input to cos(x), sin(x) " <<
		"and e^x, then the program compares the approximate value " <<
		"with the actual calculated value, using standard C++ functions." <<
		endl;
	return;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * This function pauses the program, until the user enters a character, and
 *then clears the screen after the user has indicated he or she wants to
 *continue
 *
 * @return void
 *
 *****************************************************************************/
void wait() {
	//This will pause th screen, and wait until the user is ready before 
	//continuing
	system("pause");
	//This will clear the screen after the pausing the screen for a little bit
	system("CLS");
	return;
}


/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * This function calculates a factorial from a given input
 *
 * @param[in]	a			This integer value is the integer that the function
 *							will find the factorial of.
 * @param[out]	factorial	This will be the number the function will spit out
 *							as the factorial value, the if statement
 *							immediately after changes the factorial value to a
 *							1 if a==0; known bug in trying to enter a negative
 *							number, however, a negative number cannot be
 *							entered for a
 * @param[in]	x			After the for loop this is the factorial of a-1
 *
 *
 * @return factorial	This is the value of the factorial
 *
 *****************************************************************************/
 //This will find the factorial of an integer, it is a long double type because
 //factorial values can get very, very big
long double factorial(int a) {
	long double factorial = a;
	//	The value for a is never given the opportunity to be a negative or zero
	//number, so there is no error correcting in this function
	//	Variable x is in the type long double for the same reason this 
	//function is
	long double x = 1;
	//this for loop is used to calculate the actual factorial value
	for (--a; a > 0; a--) {
		x *= a;
	}
	factorial *= x;
	//This returns the value of the factorial
	return factorial;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * A function to convert degrees to radians
 *
 * @param[in]      degrees		The program takes in the number of degrees
 *								and finds the number of radians from the
 *								degrees.
 * @param[out]     radians		This is the number of radians calculated from
 *								the degrees.
 *
 * @return radians.
 *
 *****************************************************************************/
double convertToRadians(double degrees) {
	// The value of pi is defined by the libraries as M_PI
	double radians = ((degrees)*(M_PI / 180.0));
	return radians;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * A function to approximate e^x
 *
 * @param[in]		x			The value that needs to be approximated
 * @param[in]		numTerms	Sort of like a level of accuracy for the
 *								calculation
 * @param[out]		temp		Approximate value for e^x function using Taylor
 *								expansion (temporary)
 *
 * @returns			temp			The e^x approximation
 *
 *****************************************************************************/
double myX(double x, int numTerms) {
	//See, the temp variable is often used in the approximation functions
	temp = 1;
	//This loop statement is where the approximation for the e^x function
	// lives
	for (int i = 1; i <= numTerms; ++i) {
		temp += (pow(x, i) / (factorial(i)));
	}
	//return the approximation value
	return temp;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * A function to approximate sin(x)
 *
 * @param[in]		x			The value that needs to be approximated
 * @param[in]		numTerms	sort of like the accuracy of the approximation
 * @param[out]		temp		A temporary value that
 *
 * @return			temp		The eventual value of the MySin function
 *
 *****************************************************************************/
double mySin(double x, int numTerms) {
	//I used temp as a temporary variable, again
	temp = 0;
	//This loop statement is where the approximation for the sin(x) function
	// lives
	for (int i = 0; i <= numTerms; i++) {
		temp += ((pow(-1.0, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1)));
	}
	//return the approximation value for the sin(x) function
	return temp;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * A function to approximate cos(x)
 *
 * @param[in]		x			The value that needs to be approximated
 * @param[in]		numTerms	sort of like the accuracy of the approximation
 * @param[out]		temp		A temporary value that
 *
 * @return			temp		The eventual value of the MyCos function
 *
 *****************************************************************************/
double myCos(double x, int numTerms) {
	//temp again
	temp = 1;
	//This is where the approximation calculator exists for cos(x)
	for (int i = 1; i <= numTerms; i++) {
		temp += ((pow(-1.0, i) * pow(x, 2 * i) / factorial(2 * i)));
	}
	//return the approximation value
	return temp;
}

// Prompt user and read number of terms to use. Repeat until they enter a
//	valid value
/**************************************************************************//**
 * @author	Steven Glasford
 *
 * @par Description:
 * Prompt user for the number of terms to be used in the approximation
 * and read number of terms to use. Repeat until they enter a valid value
 *
 * @param[out]		terms		This is the number of terms entered by the user
 * @param[out]		carryOn		A "trip switch" if it is tripped, function
 *								keeps asking for the number of terms (it will
 trip when the term entered is not in bounds)
 *
 * @returns			terms		This is how many terms that the user entered
 *
 *****************************************************************************/
int getNumTerms() {
	//The Tripping Variable
	carryOn = false;
	//a do loop asking for the number of terms, uses the tripping variable 
	// carry on to determine if the do loop should end
	do {
		cout << "How many terms do you want for "
			<< "the calculation? (0<x<21): " << flush;
		cin >> terms;
		//If the number entered is between the boundaries, the function
		// will set the carryOn to true, which will make the !(carryOn)
		// false and the program will exit
		if ((terms > 0) && (terms < 21)) {
			carryOn = true;
			cout << "\nYou entered " << terms << " number of terms" << endl;
		}

		else {
			cout << "Sorry but that was not acceptable input, please try again, "
				<< endl;
			carryOn = false;
		}

	} while (!carryOn);

	return terms;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This function gets the values for e^x
 *
 * @param[out]		xValue		A temporary value where the value of the x
 *								term is entered by the user
 * @param[out]		carryOn		A "tripping" variable, if the variable is
 *								tripped to true, the do loop will end
 *
 * @returns			xValue		The value entered by the user under the right
 *								conditions
 *
 *****************************************************************************/
double getX() {
	double xValue = 0;
	//The Tripping Variable
	carryOn = false;
	//a do loop asking for the number of terms, uses the tripping variable 
	// carry on to determine if the do loop should end
	do {
		cout << "\nEnter the number you would like to approximate"
			<< " (0 <= x <= 5): " << flush;
		cin >> xValue;
		//If the number entered is between the boundaries, the function
		// will set the carryOn to true, which will make the !(carryOn)
		// false and the program will exit
		if ((xValue >= 0) && (xValue <= 5)) {
			cout << "\nYou entered " << xValue << endl << endl;
			carryOn = true;
		}
		//This else statement ends the tripping loop
		else {
			cout << "Sorry but that was not acceptable input, "
				<< "please try again, " << endl;
			carryOn = false;
		}
	} while (!carryOn);
	return xValue;
}

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Description:
 * Prompt user and read x in degrees. Repeat until they enter a valid value
 *
 * @param[in]		degrees		A temporary value where the number of degrees
 *								is entered by the user
 * @param[out]		carryOn		A "tripping" variable, if the variable is
 *								tripped to true, the do loop will end
 *
 * @returns			degrees		Returns the number of degrees entered by
 the user.
 *
 *****************************************************************************/
double getDegrees() {
	double degrees = 0;
	//tripping variable at it again
	carryOn = false;
	do {
		cout << "\nEnter the number of degrees you would like (-180 <="
			<< " x <= 180): " << flush;
		cin >> degrees;
		//If the number entered is between the boundaries, the function
		// will set the carryOn to true, which will make the !(carryOn)
		// false and the program will exit
		if ((degrees <= 180) && (degrees >= -180)) {
			cout << "\nYou entered " << degrees << " degrees" << endl;
			carryOn = true;
		}
		// the function will loop if degrees are out of bounds
		else {
			cout << "Sorry but that was not acceptable input, "
				<< "please try again, " << endl;
			carryOn = false;
		}
	} while (!carryOn);

	return degrees;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * Prints out the first menu choices, without any inputs or outputs
 *
 * @return			void
 *
 *****************************************************************************/
void menuList() {
	//Output the menu choices
	cout << "Please choose one of the following functions to approximate\n"
		<< "\n1.\te^x\n" << "2.\tsin(x)\n" << "3.\tcos(x)\n" <<
		"\n4.\tExit the program" << endl;
	//Don't return anything
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * Calculates the duration between begin and end clocks
 *
 * @param[in]		begin		A value of the beginning of the clock
 * @param[in]		end			A value of the ending of the clock
 * @param[out]		time		The difference in the time of begin and end
 *								in nanoseconds
 *
 * @returns			time		Outputs the duration between two times (begin
 *								and end)
 *
 *****************************************************************************/
int duration(chrono::high_resolution_clock::time_point begin,
	chrono::high_resolution_clock::time_point end) {
	//This will calculate the amount of time in nanoseconds it took between 
	//begin and end and then convert that number into integer type
	int time = static_cast<int>(chrono::duration_cast<chrono::nanoseconds>
		(end - begin).count());
	return time;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This calculates an average of all of the times it took to get an answer
 * it uses the values in timeArray to get an average
 *
 * @param[in]		timeArray[i]	This is a temporary place for all of the
 *									the times it took to calculate
 * @param[out]		averageTime		This is the average time it took to make
 *									a calculation
 *
 * @returns			averageTime		Returns the calculated average time
 *
 *****************************************************************************/
int timeAverage() {
	int averageTime = 0;
	//This will add up all of the values stored in timeArray[]
	for (int i = 0; i < TIME_LOOPS; i++) {
		averageTime += timeArray[i];
	}
	//This will divide the number of entries in timeArray[] by the sum
	// of all of the entries in timeArray[]
	averageTime /= TIME_LOOPS;
	//This returns the average time
	return averageTime;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This function deals with most of the calculations and controls of the e^x
 * function and approximation, along with the clockings and more
 *
 * @param[in]		timeArray[]		This will be the location where the list
 of times will be located
 * @param[in]		begin			This is the beginning of a clock, and is
 a temporary placement for the general
 beginning of a duration
 * @param[in]		end				This is the ending of a clock, and is
 a temporary placement for the general
 ending of a duration
 * @param[in]		terms			This is the number of terms to use in the
 approximations
 * @param[in]		xxx				This the value that is approximated/
 calculated
 * @param[in]		approx			This is the value of the approximate value
 * @param[in]		timeApprox		This is the average time taken to a
 calculation, uses timeAverage() to find
 * @param[in]		TIME_LOOPS		This is the number of times the calculation
 is carried out to and the size of the
 timeArray.
 * @param[in]		actual			This is actual calculated value of xxx
 using the standard math libraries
 * @param[in]		timeActual		This is the average amount of time it took
 find the actual value
 * @param[in]		i				Used to control the loops
 *
 * @return			void
 *
 *****************************************************************************/
void xDeal() {
	//These two declarations are used to initialize both begin and end
	chrono::high_resolution_clock::time_point begin;
	chrono::high_resolution_clock::time_point end;
	//Repeat to the user which choice they have taken
	cout << "\nYou have chosen to approximate e^x\n" << endl;
	//get and store the number of terms the user wishes to approximate to
	terms = getNumTerms();
	//get and store the number the user wants to run the calculations against
	xxx = getX();
	//the next two loops run the calculation a bunch of times (100000 times) 
	// and averages the amount of time it took to run the calculation
	for (int i = 0; i < TIME_LOOPS; i++) {
		//Start the clock now
		begin = chrono::high_resolution_clock::now();
		//run the approximation calculation
		approx = myX(xxx, terms);
		//end the clock now
		end = chrono::high_resolution_clock::now();
		//store the duration between begin and end in timeArray[]
		timeArray[i] = duration(begin, end);
	}
	//calculate and store the average time for the approximation calculations
	int timeApprox = timeAverage();
	for (int i = 0; i < TIME_LOOPS; i++) {
		//Start the clock now
		begin = chrono::high_resolution_clock::now();
		//Run the actual calculation
		actual = exp(xxx);
		//end the clock now
		end = chrono::high_resolution_clock::now();
		//store the duration between begin and end in timeArray[i]
		timeArray[i] = duration(begin, end);
	}
	//calculate and store the average time for the approximation calculations
	int timeActual = timeAverage();
	//set the number of decimal points to 8, then output all of the needed 
	// value
	cout << fixed << setprecision(8) << "Approximate value: "
		<< approx << "\nTime needed to execute in nanoseconds: " << timeApprox <<
		"\nThe actual calculated value: " << actual <<
		"\nTime needed to execute in nanoseconds: " << timeActual << endl;
	//wait for a second before continuing, and then clear the screen, and 
	// reloop
	wait();
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This is used to get the terms and degrees used in the trig calculations.
 *
 * @param[in,out]		terms		This is how many terms there should be in
 in the expansion.
 * @param[in,out]		degrees		This is the number of degrees the program
 should use in its calculations.

 *
 * @returns void
 *
 *****************************************************************************/
void trigTerms(int& terms, double& degrees) {
	//get the number of terms and store the number of terms into the variable 
	// terms
	terms = getNumTerms();
	//get the number of degrees and store that number of into th variable
	// degrees
	degrees = getDegrees();
	//returns void
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This function does two things, the first is that it converts the number of
 * degrees entered by the user earlier to radians, the second is that it
 * the average amount of time required to calculate those radians. The program
 * returns the average time back to the other function.
 *
 * @param[in]		timeArray[]		A place for the duration of the
 *									calculations, used again later on to find
 *									average time required to convert to radians
 * @param[in]		begin			Starting the Clock
 * @param[in]		end				Stopping of the clock
 * @param[in]		i				Used to control the loops
 * @param[in]		degrees			User inputs this value
 * @param[in]		radians			The number of radians in such and such
 *									degrees
 * @param[in]		TIME_LOOPS		Used to determine how many times the
 *									function should run the calculation
 * @param[out]		time			The average time spent to convert degrees
 *									to radians
 *
 * @returns			time			The average amount of time it took to run
 *									the calculation
 *
 *****************************************************************************/
int clockRadians(double degrees) {
	//These two declarations are used to initialize both begin and end
	chrono::high_resolution_clock::time_point begin;
	chrono::high_resolution_clock::time_point end;
	//This will run the same calculation a bunch of time (how many times
	//is given by the constant integer TIME_LOOPS, and it will also 
	//find the duration between the calculations, and store those durations
	//in timeArray
	for (int i = 0; i < TIME_LOOPS; i++) {
		//start the clock
		begin = chrono::high_resolution_clock::now();
		//run the calculations
		radians = convertToRadians(degrees);
		//end the clock
		end = chrono::high_resolution_clock::now();
		//store the duration value into entries for timeArray[]
		timeArray[i] = duration(begin, end);
	}
	//This will find the average of all of the times stored in timeArray
	//and will store it for the variable time
	int time = timeAverage();
	//This will output the converted radian value
	cout << "\nWhich is " << radians << " number of radians" << endl;
	//This returns the average time value
	return time;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This function deals with most of the calculations and controls of the e^x
 * function and approximation, along with the clockings and more
 *
 * @param[in]		timeArray[]		This will be the location where the list
 of times will be located
 * @param[in]		begin			This is the beginning of a clock, and is
 a temporary placement for the general
 beginning of a duration
 * @param[in]		end				This is the ending of a clock, and is
 a temporary placement for the general
 ending of a duration
 * @param[in]		terms			This is the number of terms to use in the
 approximations
 * @param[in]		radians			This the value that is approximated/
 calculated
 * @param[in]		approx			This is the value of the approximate value
 * @param[in]		timeApprox		This is the average time taken to a
 calculation, uses timeAverage() to find
 * @param[in]		TIME_LOOPS		This is the number of times the calculation
 is carried out to and the size of the
 timeArray.
 * @param[in]		actual			This is actual calculated value of xxx
 using the standard math libraries
 * @param[in]		timeActual		This is the average amount of time it took
 find the actual value
 * @param[in]		i				Controls the loops
 *
 * @return			void
 *
 *****************************************************************************/
void sineDeal() {
	//These two declarations are used to initialize both begin and end
	chrono::high_resolution_clock::time_point begin;
	chrono::high_resolution_clock::time_point end;
	//repeat to the user what option they have chosen
	cout << "\nYou have chosen to approximate sin(x)" << endl;
	//this function will get and store the both of the values 
	// terms and degrees
	trigTerms(terms, degrees);
	// this will determine the amount of time it took to 
	int timeRadians = clockRadians(degrees);
	//The next for loops things find the averages (from 100000 iterations) of 
	// the amount of time taken to do calculations
	for (int i = 0; i < TIME_LOOPS; i++) {
		//start the clock
		begin = chrono::high_resolution_clock::now();
		//run the approximation calculation
		approx = mySin(radians, terms);
		//end the clock
		end = chrono::high_resolution_clock::now();
		//store the duration of time between begin and end in the entries in
		// timeArray[]
		timeArray[i] = duration(begin, end);
	}
	// calculate and store the average calculation time plus the timeRadians
	// value in for timeApprox
	int timeApprox = timeAverage() + timeRadians;

	for (int i = 0; i < TIME_LOOPS; i++) {
		//Starts the clock
		begin = chrono::high_resolution_clock::now();
		//Run the calculation
		actual = sin(radians);
		//end the clock
		end = chrono::high_resolution_clock::now();
		//store the duration between begin and end in the entries of 
		//timeArray[]
		timeArray[i] = duration(begin, end);
	}
	//calculate and store the average calculation duration plus the duration
	// it took to find the number of radians in timeActual
	int timeActual = timeAverage() + timeRadians;
	//print the necessary information
	cout << fixed << setprecision(8) << "Approximate value: "
		<< approx << "\nTime needed to execute in nanoseconds: " << timeApprox <<
		"\nThe actual calculated value: " << actual <<
		"\nTime needed to execute in nanoseconds: " << timeActual << endl;
	//make the user wait a little bit then when they want to continue, clear 
	//the screen and reloop
	wait();
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This function deals with most of the calculations and controls of the e^x
 * function and approximation, along with the clockings and more
 *
 * @param[in]		timeArray[]		This will be the location where the list
 of times will be located
 * @param[in]		begin			This is the beginning of a clock, and is
 a temporary placement for the general
 beginning of a duration
 * @param[in]		end				This is the ending of a clock, and is
 a temporary placement for the general
 ending of a duration
 * @param[in]		terms			This is the number of terms to use in the
 approximations
 * @param[in]		xxx				This the value that is approximated/
 calculated
 * @param[in]		approx			This is the value of the approximate value
 * @param[in]		timeApprox		This is the average time taken to a
 calculation, uses timeAverage() to find
 * @param[in]		TIME_LOOPS		This is the number of times the calculation
 is carried out to and the size of the
 timeArray.
 * @param[in]		actual			This is actual calculated value of xxx
 using the standard math libraries
 * @param[in]		timeActual		This is the average amount of time it took
 find the actual value
 *
 * @return			void
 *
 *****************************************************************************/
void cosineDeal() {
	//These two declarations are used to initialize both begin and end
	chrono::high_resolution_clock::time_point begin;
	chrono::high_resolution_clock::time_point end;
	//repeat the choice the user chose took to the user
	cout << "\nYou have chosen to approximate cos(x)" << endl;
	//find and store the values terms and degrees
	trigTerms(terms, degrees);
	//find and store the average time it took to convert the number
	// of radians in degrees
	int timeRadians = clockRadians(degrees);
	//the next two loops calculate an average (from 100000 iterations) speed 
	// for the amount of time needed to execute the calculations
	for (int i = 0; i < TIME_LOOPS; i++) {
		//start the clock
		begin = chrono::high_resolution_clock::now();
		//run the approximation calculation
		approx = myCos(radians, terms);
		//end the clock
		end = chrono::high_resolution_clock::now();
		//store the duration of the calculation in the 
		// entries of timeArray[]
		timeArray[i] = duration(begin, end);
	}
	//find and store the average duration of the calculation plus the time
	// it took to find the number of radians from degrees
	int timeApprox = timeAverage() + timeRadians;
	//do the same sort of thing as the above loop, except finding the actual
	// value
	for (int i = 0; i < TIME_LOOPS; i++) {
		//start the clock
		begin = chrono::high_resolution_clock::now();
		//run the calculation
		approx = cos(radians);
		//stop the clock
		end = chrono::high_resolution_clock::now();
		//store the duration of the calculation in timeArray[i]
		timeArray[i] = duration(begin, end);
	}
	//find the average of the calculation times in timeArray[]
	//then add that number to timeRadians and store for the variable timeActual
	int timeActual = timeAverage() + timeRadians;
	//print the necessary information
	cout << fixed << setprecision(8) << "Approximate value: "
		<< approx << "\nTime needed to execute in nanoseconds: " << timeApprox <<
		"\nThe actual calculated value: " << actual <<
		"\nTime needed to execute in nanoseconds: " << timeActual << endl;
	//make the user wait a little bit then when they want to continue, clear 
	//the screen and reloop
	wait();
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * Function to print a selection menu and retrieve the user's choice
 *
 * @param[in]		choice		depending on what the user enters, the function
 will react differently
 *
 * @return			choice		if choice == 4, the function will try to exit
 *
 *****************************************************************************/
int getMenuChoice() {
	//print the choices available for the user
	menuList();
	//make the user enter something for their choice
	cin >> choice;
	//do different things depending on what the user entered
	switch (choice) {
	case 1:
		//This is the choice for the e^x function
		xDeal();
		break;
	case 2:
		//This is the choice for the sin(x) function
		sineDeal();
		break;
	case 3:
		//This is the choice for the cos(x) function
		cosineDeal();
		break;
	case 4:
		//This is printed if the user wants to exit the function
		cout << "You have voluntarily chosen to end the program" << endl;
		break;
	default:
		//After producing this message the function should restart the loop
		cout << "Sorry, but that wasn't understood" << endl;
		break;
	}
	//This function should send the value of choice back to the main() function
	return choice;
}

/**************************************************************************//**
 * @author Anonymous
 *
 * @par Description:
 * Silly ASCII art of a plane, potentially used for exiting the program
 *
 * @return		void
 *
 *****************************************************************************/
void plane() {
	cout <<
		"#############################################################\n" <<
		"#                    _                                      #\n" <<
		"#                  -=\\`\\                                    #\n" <<
		"#              |\\ ____\\_\\__                                 #\n" <<
		"#            -=\\c`\"\"\"\"\"\"\" \"`)                               #\n" <<
		"#               `~~~~~/ /~~`\\                                #\n" <<
		"#                 -==/ /                                    #\n" <<
		"#                   '-'                                     #\n" <<
		"#                  _  _                 Goodbye             #\n" <<
		"#                 ( `   )_                                  #\n" <<
		"#                (    )    `)                               #\n" <<
		"#              (_   (_ .  _) _)                             #\n" <<
		"#                                             _             #\n" <<
		"#                                            (  )           #\n" <<
		"#             _ .                         ( `  ) . )        #\n" <<
		"#           (  _ )_                      (_, _(  ,_)_)      #\n" <<
		"#         (_  _(_ ,)                                        #\n" <<
		"#############################################################" << endl;
	return;
}

/**************************************************************************//**
 * @author Chris.com
 *
 * @par Description:
 * Silly ASCII art of a truck potentially used for exiting the program
 *
 * @return		void
 *
 *****************************************************************************/
void truck() {
	cout << R"(
                   _______________________________________________________
                  |                                                      |
             /    |                                                      |
            /---, |                                                      |
       -----# ==| |                      Goodbye                         |
       | :) # ==| |                                                      |
  -----'----#   | |______________________________________________________|
  |)___()  '#   |______====____   \___________________________________|
 [_/,-,\"--"------ //,-,  ,-,\\\   |/             //,-,  ,-,  ,-,\\ __#
   ( 0 )|===******||( 0 )( 0 )||-  o              '( 0 )( 0 )( 0 )||
----'-'--------------'-'--'-'-----------------------'-'--'-'--'-'--------------
		)" << endl;
	return;
}

/**************************************************************************//**
 * @author ASCII-code.com
 *
 * @par Description:
 * Silly ASCII art of a sleepy person potentially used for exiting the program
 *
 * @return		void
 *
 *****************************************************************************/
void sleepy() {
	cout << R"(
                             Goodbye
                       Z
        .,.,        z
      (((((())    z
     ((('_  _`) '
     ((G   \ |)
    (((`   " ,
     .((\.:~:          .--------------.
     __.| `"'.__      | \              |
  .~~   `---'   ~.    |  .             :
 /                `   |   `-.__________)
|             ~       |  :             :
|                     |  :  |
|    _                |     |   [ ##   :
 \    ~~-.            |  ,   oo_______.'
  `_   ( \) _____/~~~~ `--___
  | ~`-)  ) `-.   `---   ( - a:f -
  |   '///`  | `-.
  |     | |  |    `-.
  |     | |  |       `-.
  |     | |\ |
  |     | | \|
   `-.  | |  |
      `-| '
)" << endl;
	return;
}

/**************************************************************************//**
 * @author ejm
 *
 * @par Description:
 * Silly ASCII art of a night sky potentially used for exiting the program
 *
 * @return		void
 *
 *****************************************************************************/
void stars() {
	cout << R"(
   *  .  . *       *    .        .        .   *    ..
 .    *        .   ###     .      .        .            *
    *.   *        #####   .     *      * Goodbye *    .
  ____       *  ######### *    .  *      .        .  *   .
 /   /\  .     ###\#|#/###   ..    *    .      *  .  ..  *
/___/  ^8/      ###\|/###  *    *            .      *   *
|   ||%%(        # }|{  #
|___|,  \\  ejm    }|{
)" << endl;
	return;
}

/**************************************************************************//**
 * @author Christian 'CeeJay' Jensen
 *
 * @par Description:
 * Silly ASCII art of a rocket in space potentially used for exiting the
 * program
 *
 * @return		void
 *
 *****************************************************************************/
void space() {
	cout <<
		"                         .-.\n" <<
		"                        ( (\n" <<
		"                         `-'\n\n" <<
		"                    .   ,- To the Moon Alice !\n" <<
		"                   .'.\n" <<
		"                   |o|\n" <<
		"                  .'o'.\n" <<
		"                  |.-.|\n" <<
		"                  '   '\n" <<
		"                   ( )                   Goodbye\n" <<
		"                    )\n" <<
		"                   ( )\n\n" <<
		"               ____\n" <<
		"          .-'\"\"p 8o\"\"`-.\n" <<
		"       .-'8888P'Y.`Y[ ' `-.\n" <<
		"     ,']88888b.J8oo_      '`.\n" <<
		"   ,' ,88888888888[\"        Y`.\n" <<
		"  /   8888888888P            Y8\\\n" <<
		" /    Y8888888P'             ]88\\\n" <<
		":     `Y88'   P              `888:\n" <<
		":       Y8.oP '- >            Y88:\n" <<
		"|          `Yb  __             `'|\n" <<
		":            `'d8888bo.          :\n" <<
		":             d88888888ooo.      ;\n" <<
		" \\            Y88888888888P     /\n" <<
		"  \\            `Y88888888P     /\n" <<
		"   `.            d88888P'    ,'\n" <<
		"     `.          888PP'    ,'\n" <<
		"       `-.      d8P'    ,-'   -CJ-\n" <<
		"          `-.,,_'__,,.-' " << endl;
	return;
}


/**************************************************************************//**
 * @author Blackfang
 *
 * @par Description:
 * silly ASCII art of a desert potentially used for exiting the program
 *
 * @return		void
 *
 *****************************************************************************/
void desert() {
	cout <<
		"       /\\\n" <<
		"      /  \\.--./\\             Goodbye\n" <<
		"     /    \\  /  \\\n" <<
		"    /      \\/    \\        .--.\n" <<
		"   /     |\\_/|    \\       |   | .---.\n" <<
		"  /     / o o\\     \\      |   | |   | .---.\n" <<
		" /      /(   )\\     \\     |   `-'   |_|   |\n" <<
		"/       / \\#/ \\      \\    |         ._____'\n" <<
		"        |     |           `---.     |\n" <<
		"        | | | |                |    |\n" <<
		"      (~\\ | | /~)              |    |\n" <<
		"     __\\\\_|| ||_/__             |    |\n" <<
		"___///_//_| |_\\\\__\\\\\\__________|____|\n" <<
		"\nArtwork by Blackfang" << endl;
	return;
}

/**************************************************************************//**
 * @author Chris.com
 *
 * @par Description:
 * This is actual ASCII art from Obama's website source code during the 
 * 2016 election
 *
 * @return		void
 *
 *****************************************************************************/
void obamaWebsite() {
	cout <<
		"                |))    |))\n"
		"  .             |  )) /   ))            .oooooooo.    .ooooooooo.\n" <<
		"  \\\\   ^ ^      |    /      ))        -sddddddddddy:::hdddddmmmmmy-\n" <<
		"   \\\\(((  )))   |   /        ))      -ddddddhhhhhh     ddddddmmmmmd-\n" <<
		"    / G    )))  |  /        ))       sddddhhhhhhhhhhhddddddddmmmmmms\n" <<
		"   |o  _)   ))) | /       )))        odddhhhhhhhhhhhhdddddddddmmmmmo\n" <<
		"    - ' |     ))`/      )))          -hdddhhhhhhhh     dddddddmmmmh.    aHR0cDovL2loci5mbS9zZTRXWj9w\n" <<
		"     ___|              )))            -ydddhhhhhhh     ddddddmmmmy-     bmFtZT1zb3VyY2Vycg==\n" <<
		"    / __\\             ))))`()))        `+hdddddddd     ddddddmmh/`\n" <<
		"   /\\@   /             `(())))           ./ydddddd     ddddmdy:`\n" <<
		"   \\/   /  /`_______/\\   \\  ))))           `:sdddd     ddmdo-`\n" <<
		"        | |          \\ \\  |  )))              .+hm     mh+.\n" <<
		"        | |           | | |   )))               `+     /`\n" <<
		"       /_/           /_/\n\n" <<
		"  Come work with us in TriBeCa, NYC!\n" <<
		"  We're hiring JS ninjas and Python neckbeards (or vice versa. ninja outfit and neckbeard optional)\n" <<
		"  Drop a line and resume to d2Viam9ic0BpaGVhcnRyYWRpby5jb20=\n\n" <<
		"This is actually from the Obama Website during the 2016 Presidential website, and goodbye." << endl;
	return;
}

/**************************************************************************//**
 * @author		Steven Glasford
 *
 * @par Description:
 * This will generate a random number and then use the random number to
 * chose a random ASCII art piece on exiting the program, created 9-20-17.
 *
 * @param[in]		RandomThing		This is the random number used to determine
 *									the outcome of the exiting program
 *
 * @return			void
 *
 *****************************************************************************/
void exitDialog() {
	//This Sets the seed for the random numbers to come later
	srand(static_cast<int>((unsigned)
		time(NULL)));
	//This is the random number used by the function
	int randomThing = rand() % 7 + 1;
	switch (randomThing) {
	case 1:
		//This will produce ASCII art of a plane
		plane();
		break;
	case 2:
		//This will produce ASCII art of a truck
		truck();
		break;
	case 3:
		sleepy();
		//This will produce ASCII art of a sleepy person
		break;
	case 4:
		//This will produce ASCII art of a star scene
		stars();
		break;
	case 5:
		//This will produce ASCII art of a space scene 
		space();
		break;
	case 6:
		//This will produce ASCII art of a desert scene
		desert();
		break;
	default:
		//This will produce ASCII art of a obama joke
		obamaWebsite();
		break;
	}
	return;
}