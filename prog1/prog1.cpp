#include <iostream>
#include <cmath>
#include <Windows.h>
#include <iomanip>

/*************************************************************************//**
* @file
*
* @mainpage Program 1 - Beep
*
* @section CSC-150-M001
*
* @author Steven Glasford
*
* @date 9-15-2017
*
* @par Professor:
*			Larry Pyeatt
*
* @par Course:
*			CSC-150-M001
*
* @par location:
*			McLaury 306
*
 * @section program_section Program Information
 *
 * @details This program asks the user for 3 pairs of octave and pitch class 
 * values.
 * The computer then determines if the octaves are between 0 and 11, and if the
 * pairs can be heard when passed through a frequency function.
 * If and only if the octaves are between 0 and 11 as well as the sound being 
 * able
 * to be heard, will the computer produce the tones.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Compiled with Microsoft Visual Studio Community 2017, tested on 
 *Microsoft Visual Studio 2013
 *
 * @par Usage:
   @verbatim
   c:\> <prog>.exe
   d:\> c:\bin\<prog>.exe
   @endverbatim
 *
 * @section todo_bugs_modification_section To do, Bugs and Modifications.
 *
 * @todo Nothing to do.
 * @par Modifications and Development Time line:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------------
   Sept	10,	2017	I added documentation
   @endverbatim
 *
*****************************************************************************/

using namespace std;

/**************************************************************************//**
 * @author Steven Glasford
 *
 * @par Main function:
 * This is the main function of the program and it controls basically
 * everything
 *
 * @param[in]      beepTime - This controls the length of time the tone is
 * produced
 * @param[in]		oct1 - The user enters this value, and it controls the
 * octave of the first note. Can be between 0<=x<=11, else it produces and
 * error
 * @param[in]		pitchClass1 - This value is entered by the user to control
 * the pitch class of the first note
 * @param[out]		oct2 - The user enters this value, and it controls the
 * octave of the second note. Can be between 0<=x<=11, else it produces and
 * error
 * @param[in]		pitchClass2 - this value is entered by the user to control
 * the pitch class of the second note
 * @param[in]		referenceFrequency - This value is the reference frequency
 * used for the frequency calculations coming up.
 * @param[out]		dif1 - This value is for the difference values in the
 * frequency calculation up in the exponent for the first frequency.
 * @param[out]		dif2 - This value is for the difference value for the
 * second note's frequency equation.
 * @param[out]		dif2 - This value is for the difference value for the
 * third note's frequency equation.
 * @param[in]		lowestSound - This is the lowest frequency a person can
 * hear and is used to determine whether or not to play a sound.
 * @param[in]		highestSound - This is the highest frequency a person can
 * hear and is used to determine whether or not to play a sound.
 * @returns 0 program ran successful.
 * @returns 1 One of the Octaves entered was too low.
 * @return  2 One of the Octaves entered was too high.
 *
 *****************************************************************************/

 // Program actually starts
int main() {
	//	The following variable is the reference frequency used by the frequency
	//function to determine the frequency which the program will produce the
	//beep for
	const double referenceFrequency = 440.0;
	//	The following variable is constant because it corresponds to the lowest
	//frequency that a human can hear.
	//	The following variable is used to compare the frequency generated by
	//the frequency function to the lowest sound a person can hear, and if the
	//frequency from octpch is too low, an error will be produced, and the
	//program will exit.
	const int lowestSound = 37;
	//	The following variable is constant because it corresponds to the
	//highest frequency that a human can hear.
	//	The following variable is used to compare the frequency generated
	//by the frequency function to the highest sound a person can hear, and if
	//the frequency from octpch is too high, an error will be produced, and
	//the program will exit.
	const int highestSound = 30000;
	//	This variable controls the duration of the beep
	int beepTime = 1000;
	//	The next three variables are for the octaves of the notes
	int oct1 = 0;
	int oct2 = 0;
	int oct3 = 0;
	//	The next three variables are for the pitch class of octpch pair
	int pitchClass1 = 0;
	int pitchClass2 = 0;
	int pitchClass3 = 0;
	//	variables frequency1,2,3 cannot be started at zero, else an error is
	//	produced if no value is entered for a particular note
	double frequency1 = 440;
	double frequency2 = 440;
	double frequency3 = 440;
	//	The following 3 variables, are used in the calculation for the
	//frequency of the beep, specifically the exponent component of
	//the frequency function, there are three of them, for each of the
	//3 frequencies
	double dif1 = 0;
	double dif2 = 0;
	double dif3 = 0;
	

	//	Program outputs a brief, descriptive message
	//when it first starts, indicating the purpose of the program,
	//the input required, and the output that will be produced
	cout << "This program will produce 3 different \"beeps\" each\n"
		<< "having a frequency and pitch dependent on conditions\n" 
		<< "entered by the user. Each beep is played for 1 second" << endl;

	//	The computer asks for the different values octave and pitch class
	//value pair values

	cout << "Enter the octave of the first note (0<=x<=11): " << flush;
	cin >> oct1;
	//	If the value entered for the octave1 is too low, the program will
	//quit, else it continues asking for values
	if ( oct1 < 0 ) {
		cout << "The value you entered is too low, quitting now..." << endl;
		return 1;
	}
	else if ( oct1 > 11 ) {
		cout << "The value you entered is too high, quitting now..." << endl;
		return 2;
	}
	else {
		cout << "You entered " << oct1 << " for the first octave" << endl;
	}

	// enter the value for the first pitch class
	cout << "\rEnter the pitch class of the first note: " << flush;
	cin >> pitchClass1;
	cout << "You entered " << pitchClass1 << " for the first pitch class" 
		<< endl;

	//	Enter the value for the second octave
	cout << "\rEnter the octave of the second note (0<=x<=11): " << flush;
	cin >> oct2;

	//	If the value entered for the octave2 is too low, or too high, the
	//program will quit; else the program continues
	if ( oct2 < 0 ) {
		cout << "The value you entered is too low, quitting now..." << endl;
		return 1;
	}
	else if ( oct2 > 11 ) {
		cout << "The value you entered is too high, quitting now..." << endl;
		return 2;
	}
	else {
		cout << "You entered " << oct2 << " for the second octave" << endl;
	}

	cout << "\rEnter the pitch class of the second note: " << flush;
	cin >> pitchClass2;
	cout << "You entered " << pitchClass2 << " for the second pitch class" 
		<< endl;

	cout << "\rEnter the octave of the third note (0<=x<=11): " << flush;
	cin >> oct3;
	// If the value entered for the octave3 is too low, or too high, the
	//program will quit; else the computer continues
	if ( oct3 < 0 ) {
		cout << "The value you entered is too low, quitting now..." << endl;
		return 1;
	}
	else if ( oct3 > 11 ) {
		cout << "The value you entered is too high, quitting now..." << endl;
		return 2;
	}
	else {
		cout << "You entered " << oct3 << " for the third octave" << endl;
	}

	cout << "\rEnter the pitch class of the third note: " << flush;
	cin >> pitchClass3;
	cout << "You entered " << pitchClass3 << " for the third pitch class" 
		<< endl;

	// Calculate the frequency of each beep
// The following three variables correspond to the exponential component
//of the frequency equation
	dif1 = ((static_cast<double>(oct1) - 4) +
		((static_cast<double>(pitchClass1) - 9) / 12));
	dif2 = ((static_cast<double>(oct2) - 4) +
		((static_cast<double>(pitchClass2) - 9) / 12));
	dif3 = ((static_cast<double>(oct3) - 4) +
		((static_cast<double>(pitchClass3) - 9) / 12));

	// These next three store the different frequencies
	frequency1 = ( referenceFrequency * pow( 2.0, dif1 ) );
	frequency2 = ( referenceFrequency * pow( 2.0, dif2 ) );
	frequency3 = ( referenceFrequency * pow( 2.0, dif3 ) );

	// Calculate whether the beeps are within human auditory range, and
	// print the notes that cannot be heard

	// See if the first note is too low to be heard
	if ( frequency1 <= lowestSound ) {
		cout << "The frequency of the first note is too low ";
		cout << "to be able to be heard by humans" << endl;
	}
	// See if the first note is too high to be heard
	else if ( frequency1 >= highestSound ) {
		cout << "The frequency of the first note is too high "
			<< "to be able to be heard by humans" << endl;
	}
	// Produce the first sound if it can be heard
	else {
		cout << "Frequency of the first note: " << frequency1
			<< "Hz." << endl;
		Beep(static_cast<int>(frequency1), beepTime);
	}

	// See if the second note is too low to be heard
	if ( frequency2 <= lowestSound ) {
		cout << "The frequency of the second note is too low "
			<< "to be able to be heard by humans" << endl;
	}
	// See if the second note is too high to be heard
	else if ( frequency2 >= highestSound ) {
		cout << "The frequency of the second note is too high "
			<< "to be able to be heard by humans" << endl;
	}
	// Produce the second note if the aforementioned statements are false
	else {
		cout << "Frequency of the second note: " << frequency2
			<< "Hz." << endl;
		Beep(static_cast<int>(frequency2), beepTime);
	}

	// See if the third note is too low to be heard
	if ( frequency3 <= lowestSound ) {
		cout << "The frequency of the third note is too low "
			<< "to be able to be heard by humans" << endl;
	}
	// See if the third note is too high to be heard
	else if ( frequency3 >= highestSound ) {
		cout << "The frequency of the third note is too high "
			<< "to be able to be heard by humans" << endl;
	}
	// Produce the third note if the aforementioned statements are false
	else {
		cout << "Frequency of the third note: " << frequency3;
		cout << "Hz." << endl;
		Beep(static_cast<int>(frequency3), beepTime);
	}

	// exit safely after finishing the program
	return 0;
}