#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	//the number the user inputs to be taken to the root of
	double number = 0;
	//the root to take of the above number
	double root = 0;
	//How may iterations should be taken
	int terms = 0;
	//determines whether or not the program should exit
	char exit = 'Y';

	//	This loop will quit if someone enters the letter 'n' when asked to 
	//continue or not
	do {
		//ask the user how many iterations of the root should be taken
		cout << "How many terms? " << flush;
		cin >> terms;
		//ask the user for the number to take the root of
		cout << "Starting value? " << flush;
		cin >> number;
		//ask the user to what root the number should be taken
		cout << "Which root? " << flush;
		cin >> root;

		//outputs the very first value, with 6 decimal places
		cout << "Starting value: " << fixed << setprecision(6) << number << endl;
		//prints out the roots, in a loop, with i being the number of iterations, 
		//with the number of iterations being less than the number of terms, since
		//the i value starts at zero
		for (int i = 1; i <= terms; ++i) {
			//change the value of variable number to the root of that number
			number = pow(number, 1.0 / root);
			//print the root values, with 15 spaces between the numbers
			cout << setw(15) << number;
			if (i % 5 == 0)
				cout << endl;
		}
		
		//ask the user whether or not to continue
		cout << "\n\nContinue (Y/N) " << flush;
		cin >> exit;
		//convert the exit variable to an upper case
		exit = toupper(exit);
		//if the value entered for exit is not Y or N, the program asks the user
		//to input a new exit character
		while (!(exit == 'Y') && !(exit == 'N')) {
			cout << "Sorry but I didn't understand that, please enter something else"
				<< endl;
			//input for the exit variable again
			cin >> exit;
			//convert the exit variable to an upper case again
			exit = toupper(exit);
		}
		//print a new line and flush the buffer
		cout << endl;
	//exit the loop if 'N' is entered
	} while (!(exit == 'N'));

	return 0;
}