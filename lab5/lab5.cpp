#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// function to determine the number of people needing to be vaccinated
double transmissionLevel(char a, char b) {
	// constant values used to represent r0
	const double measles_high = 18;
	const double measles_low = 12;
	const double polio_high = 7;
	const double polio_low = 5;
	const double ebola_high = 2.5;
	const double ebola_low = 1.5;
	double pop = 0;

	// determining the percentage of people needing to be immunizing for measles
	if (a == 'M') {
		// for high transmission level
		if (b == 'H') {
			pop = (1 - 1 / measles_high);
		}
		// for low transmission level
		if (b == 'L') {
			pop = (1 - 1 / measles_low);
		}
	}
	// determining the percentage of people needing to be immunizing for polio
	if (a == 'P') {
		// for high transmission level
		if (b == 'H') {
			pop = (1 - 1 / polio_high);
		}
		// for low transmission level
		if (b == 'L') {
			pop = (1 - 1 / polio_low);
		}
	}
	// determining the percentage of people needing to be immunizing for ebola
	if (a == 'E') {
		// for high transmission level
		if (b == 'H') {
			pop = (1 - 1 / ebola_high);
		}
		// for low transmission level
		if (b == 'L') {
			pop = (1 - 1 / ebola_low);
		}
	}
	return pop;
}

int main(){
	// set at 'a' so as to not encounter an error 
	char disease = 'a';
	char spread = 'a';

	// a do loop of asking the user for inputs
	do {
		cout << "Enter the disease to estimate: \n" <<
			"\tM: Measles\n" << "\tP: Polio\n" <<
			"\tE: Ebola\n" << "\tQ: Quit" << endl;
		// user users the disease to estimate
		cin >> disease;
		disease = toupper(disease);

		// quit program if user enters 'q'
		if ((disease == 'M') || (disease == 'E') || (disease == 'P')) {
			cout << "\nEnter the factor of transmission\n" <<
				"\tH: High\n" << "\tL: Low" << endl;
			// user enters the factor of transmission
			cin >> spread;
			spread = toupper(spread);
			if ((spread == 'H') || (spread == 'L')) {
				// outputs the minimum amount of people needing to be vacinated
				cout << "Minimum percentage of population that must be immunized: " <<
					fixed << setprecision(2) << transmissionLevel(disease, spread) * 100
					<< endl;
			}
			else {
				cout << "Invalid input for high/low factor, program ending" << endl;
				return 2;
			}
			
		}
		else if (disease == 'Q') {
			cout << "ending program" << endl;
			return 1;
		}
		else {
			cout << "Invalid input for disease, program ending" << endl;
			return 2;
	}

	} while (disease != 'Q');

	return 0;
}

