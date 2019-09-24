// lab61.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//The number of minutes the person runs
	int minutes = 0;
	//the initial value for the while loop
	int i = 0;
	// the number of calories burned
	double calories = 0;
	//this number is used get rid of any value over the actual number of minutes
	int number = 0;
	//ask the user how many minutes the person was on the treadmill today
	cout << "How many minutes on the treadmill today? " << flush;
	cin >> minutes;
	//make a little table to display the number of minutes and the calories burned
	cout << "Minutes";
	//set the table width to 20
	cout << setw(20) << "Calories burned" << endl;
	//prevents the list of minutes to go over the actual number of minutes run
	number = minutes / 5;
	//loops until the number for i is greater than or equal to the variable number
	while (i < number) {
		i++;
		calories += 19.5;
		//multiply i by 5 to get the numbers in intervals of 5
		cout << fixed << setprecision(2) << i*5 << setw(15) << calories << endl;
	}

	return 0;
}

