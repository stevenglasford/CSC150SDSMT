/*************************************************************************//**
* @file 
*
* @mainpage Program 3 - Voting
*
* @section CSC-150-M001 Computer Science 150
*
* @author Steven Glasford
*
* @date 10-27-2017
*
* @par Professor:
*			Dr. Pyeatt
*
* @par Course:
*			CSC-150-M001-AM
*
* @par Location:
*			McLaury - 313
*
* @section program_section Program Information
*
* @details This program simulates 500 elections, where the the election is 
* very close, the program also produces "errors" in the voting to 
* simulate the real errors that could potentially be encountered in real
* life voting machines, and then prints the number of error elections
*
* @section Compiling Instructions:
*			Tested on Visual Studio 2013, as well as Visual Studio 2017 
*			Community edition, as well as G++.
* @par Usage:
  @verbatim
  c:\> prog3.exe
  d:\> c:\bin\prog3.exe
  @endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug None so far detected
*
* @todo Finish documentation
*
* @par Modifications and Development Timeline:
  @verbatim
   Date          Modification 
   ------------  --------------------------------------------------------------
   10-15-2017	 Built Program, completed debugging, tested on G++, VS 2013
				 and VS 2017 Community
   10-24-2017	 Finished documentation
  @endverbatim
*
*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <limits>


using namespace std;

/*!
 *@brief This variable is determines the number of elections that will be held
 * it is 16 bit integer since it isn't very large 
 * (less than 16000 or whatever)
 */
//can be a 16 bit integer since it never changes, 
//	and it is below 16,000 or whatever
const int16_t elections = 500;


/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * This function produces a short introduction, which is only showed once 
 * throughout the program's execution
 * 
 * @returns void
 * 
 *****************************************************************************/
//produce a short introduction to be shown only once 
void beforeIntroduction() {
	cout << "This program simulates voting in 500 districts, where the actual" <<
		"\noutcome of the election should be exactly 50.5% for " <<
		"candidate A, \n" << "and 49.5% for candidate B. This program will" <<
		"randomly produce an error\n" << "dependent on the machine error " << 
		"given. This program will also ask for a \n" << "margin of error, " << 
		"and will use this value to determine whether or not the\n" <<
		"program witnessed an error.\n" << endl;
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * This function produces a short introduction, which basically tells the user
 * how the program is going to ask the user for input information
 * 
 * @returns void
 * 
 *****************************************************************************/
//produce a short introduction for the user
void introduction() {
	cout << "Enter voting simulation parameters. All values must be " <<
		"positive\n and greater than 0. Margin and error are entered as" <<
		" percentages (do not use the % sign) \nand cannot exceed 100." << 
		endl;
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 *
 * @par Description: 
 * This function filters through the values entered for the number of votes
 * 
 * @param[in,out]	nvotes - This is the variable being filtered
 * 
 * @returns void
 * 
 *****************************************************************************/
//filter through the values entered for the number of votes
void filter_nvotes(int64_t& nvotes) {
	//ask for the value again if the value entered is between 1 and 100
	while (nvotes < 1) {
		cout << "Please enter something else (you must enter something" <<
			" greater than 1): " << flush;
		cin >> nvotes;
	}
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * This funtion filters through the values entered for the margin of error
 * 
 * @param[in,out]	margin - This is the variable being scrubed by the function  
 * 
 *****************************************************************************/
//filter through the values entered for the margin of error
void filter_margin(int32_t& margin) {
	//ask for the value again if the value is between 1 and 50
	while ((margin < 1) || (margin > 50)) {
		cout << "Please enter something else (you must enter something" <<
			" greater than 1, but less than 50): " << flush;
		cin >> margin;
	}
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * This funtion filters through the values entered for the machineError
 * 
 * @param[in,out]	machineError - 	This is the variable being scrubed by 
 *									the function  
 * 
 *****************************************************************************/
//filter through the values entered for machineError
void filter_machineError(int32_t& machineError) {
	//ask for the value again if te value is between 1 and 100
	while ((machineError < 1) || (machineError > 100)) {
		cout << "Please enter something else (you must enter something" <<
			" greater than 1, but less than 100): " << flush;
		cin >> machineError;
	}
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * Get and filter through the parameters for margin, nvotes, and machineError
 * 
 * @param[in,out]	nvotes -		The number of votes cast per election
 * @param[in,out]	margin - 		The margin of error
 * @param[in,out]	machineError -	The amount of machine induced errors
 * 
 * @returns void
 * 
 *****************************************************************************/
//get and filter through the parameters for margin, nvotes, and machineError
void get_params(int64_t& nvotes, int32_t& margin, int32_t& machineError) {
	cout << "\nEnter the total number of votes cast: " << flush;
	//input the number of votes
	cin >> nvotes;
	//filter through the values entered by the user for nvotes
	filter_nvotes(nvotes);
	cout << "Enter the election margin percentage: " << flush;
	//input the margin of error
	cin >> margin;
	//filters through the values entered by the user for margin
	filter_margin(margin);
	cout << "Enter voting machine error percentage: " << flush;
	//input the amount of error produced by the machine
	cin >> machineError;
	//filters through the values entered by the user for machineError
	filter_machineError(machineError);
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * Conviently displays the errorValue, number of Errors, and the initial values
 * 
 * @param[in]	nvotes			- The number of votes cast per election
 * @param[in]	margin			- The margin of error in the race
 * @param[in]	machineError	- The amount of error produced by the voting 
 *								  machine
 * @param[in]	numError		- The number of erronous elections
 * @param[in]	errorValue		- The percentage of erronous elections to 
 *								  correct elections
 * 
 * @returns void
 * 
 *****************************************************************************/
//convientently displays the errorValue, number of errors, and more
void display_summary(int64_t nvotes, int32_t margin, int32_t machineError,
	int16_t numError, double errorValue) {
	cout << "** Election Machine Summary **\n" << "\nNumber of votes: " 
		<< nvotes << "\nElection margin: " << margin << "%" << 
		"\nMachine error rate: " << machineError << "%\n\n" << "For " << 
		elections << " runs, " << numError << 
		" incorrect elections occurred, for an error rate of " 
		<< errorValue << "%\n" << endl;
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * Find the number of errors in the voting calculations, and calculate he 
 * error rate
 * 
 * 
 * @param[in]	nvotes			- The number of votes being cast
 * @param[in]	margin			- The margin of error in the elections
 * @param[in]	machineError	- The amount of error being produced in the 
 *								  voting machines
 * @param[in]	votes[][2]		- An array containing the vote count of the 
 *								  elections
 * 
 * @returns void
 * 
 *****************************************************************************/
//find the number of errors in the voting calculations, and calculate the 
//	error rate
void calc_error(int64_t votes[][2], int64_t nvotes, int32_t margin, int32_t machineError) {
	//doesn't need to be that big of a number since the number of errors cannot exceed 500
	int16_t numError = 0;
	double errorValue = 0;
	//finds the number of elections where the number of votes was off
	for (int16_t i = 0; i < elections; i++) {
		if (margin < abs(static_cast<int64_t>(((votes[i][0] - .505 * 
			static_cast<double>(nvotes)) / (.505 * static_cast<double>
			(nvotes)) * 100)))) {
			//add to the number of errors found
			numError++;
		}
	}
	//calculates the errorValue
	errorValue = (static_cast<double>(numError) / static_cast<double>
		(elections)) * 100.0;
	//link to another another function called display_summary
	display_summary(nvotes, margin, machineError, numError, errorValue);
	//return nothing
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * Simulates the actual voting, and at the same time simulates the errors
 * 
 * 
 * @param[in]	nvotes			- The number of votes being cast
 * @param[in]	margin			- The margin of error in the elections
 * @param[in]	machineError	- The amount of error being produced in the 
 *								  voting machines
 * @param[in]	votes[][2]		- An array containing the vote count of the 
 *								  elections
 * 
 * @returns void
 * 
 *****************************************************************************/
//simulate the voting
void voting(int64_t votes[][2], int64_t nvotes, int32_t margin, 
	int32_t machineError) {
	//can be a very big number so it needs to be a 64 bit integer
	int64_t votesForHilary = 0;
	//needs to be a 64 bit number because it can be a very big number
	int64_t votesForDonald = 0;
	//gets a random number from the cryptographically secure random 
	//	number generator built into the computer
	srand(unsigned(time(NULL)));
	
	for (int16_t i = 0; i < elections; i++) {
		votesForHilary = 0;
		votesForDonald = 0;
		//needs to be a 64 bit number since j can be really big
		int64_t j = 0;
		//simulate the voting
		for (j; j < static_cast<int64_t>((nvotes * .505)); j++) {
			//randomly changes a vote for a candidate, to a vote for the other candidate
			if ((rand() % 1000) < machineError * 10) {
				votesForDonald++;
			}
			//if the computer doesn't randomly change the vote then it just adds to the 
			//	candidate it was supposed to in the first place
			else {
				votesForHilary++;
			}
		}
		for (j; j < nvotes; j++) {
			//randomly changes a vote for a candidate, to a vote for the other candidate
			if ((rand() % 1000) < machineError * 10) {
				votesForHilary++;
			}
			//if the computer doesn't randomly change the vote then it just adds to the 
			//	candidate it was supposed to in the first place
			else {
				votesForDonald++;
			}
		}
		//store the votes in the matrix
		votes[i][0] = votesForHilary;
		votes[i][1] = votesForDonald;
		
	}
	//sends new information to the next function
	calc_error(votes, nvotes, margin, machineError);
	return;
}

/**************************************************************************//** 
 * @author <Firstname Lastname>
 * 
 * @par Description: 
 * A detailed description of the function.  It can
 * extend to multiple lines
 * 
 * @param[in,out]	carryOn - Used to check if the loops should continue or not
 * 
 * @returns void
 * 
 *****************************************************************************/
//ask if the user wants to continue
void askToContinue(bool& carryOn) {
	char runAnother = 'N';
	//ask the user if he or she wishes to continue
	cout << "\nDo you wish to Continue? (Y/N): " << flush;
	//user inputs a letter
	cin >> runAnother;
	//convert the letter entered to an uppercase
	runAnother = toupper(runAnother);
	//repeatedly ask the user to input a valid letter if the letter
	//	is not y,Y,N, or n
	while ((runAnother != 'Y') && (runAnother != 'N')) {
		cout << "Sorry but that was not recognized (Y/N): " << flush;
		cin >> runAnother;
		//convert the number entered to an uppercase letter
		runAnother = toupper(runAnother);
	}
	//change carryOn to false if the letter entered was N or n
	if (runAnother == 'N') {
		carryOn = false;
	}
	//change the carryOn to true if the letter entered was Y or y
	else {
		carryOn = true;
	}
	//return nothing
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * The loopy component of the function, continuously asking the user whether or
 * not he or she wants to continue after the first run of the program
 * 
 * @param[in]	nvotes			- The number of votes being cast
 * @param[in]	margin			- The margin of error in the elections
 * @param[in]	machineError	- The amount of error being produced in the 
 *								  voting machines
 * @param[in]	votes[][2]		- An array containing the vote count of the 
 *								  elections
 * 
 * @returns void
 * 
 *****************************************************************************/
//make the program loop, consuming some of the statements that could have been found
//	in the main function
void loopy(int64_t nvotes, int32_t margin, int32_t machineError, int64_t votes[][2]) {
	//if switched to false the program exits
	bool carryOn = true;
	do {
		//a quick introduction to the program
		introduction();
		//get the parameters
		get_params(nvotes, margin, machineError);
		//do the actual voting
		voting(votes, nvotes, margin, machineError);
		//ask whether or not to continue with the loop and with the program
		askToContinue(carryOn);
		//continue with the program if carryOn is anything but false
	} while (carryOn);
	return;
}

/**************************************************************************//** 
 * @author Steven Glasford
 * 
 * @par Description: 
 * The main function
 * 
 * @returns 0 program ran successful.
 * 
 *****************************************************************************/
int main() {
	int64_t nvotes = 0;
	//doesn't need to be a 32 bit number but it is to avoid a buffer overflow
	int32_t margin = 0;
	//does not need to be a 32 bit number but it is to avoid buffer overflows
	int32_t machineError = 0;
	//needs to be a 64 bit number since it can be a really big number
	int64_t votes[elections][2];
	//a quick introduction to the purpose of the program
	beforeIntroduction();
	loopy(nvotes, margin, machineError, votes);
	return 0;
}