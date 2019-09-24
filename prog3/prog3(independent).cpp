#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;

const int elections = 500;

void introduction() {
	cout << "Enter voting simulation parameters. All values must be " <<
		"positive and greater than 0. Margin and error are entered as" <<
		" percentages (do not use the % sign) and cannot exceed 100." << endl;
	return;
}

void filter_nvotes(int& nvotes) {
	while (nvotes < 1) {
		cout << "Please enter a something else (You must enter something" <<
			" greater than 1): " << flush;
		cin >> nvotes;
	}
	return;
}

void filter_margin(int& margin) {
	while ((margin < 1) || (margin > 50)) {
		cout << "Please enter something else (you must enter something" <<
			" greater than 1, but less than 50): " << flush;
		cin >> margin;
	}
	return;
}
void filter_machineError(int& machineError) {
	while ((machineError < 1) || (machineError > 100)) {
		cout << "Please enter something else (you must enter something" <<
			" greater than 1, but less than 100): " << flush;
		cin >> machineError;
	}
}

void get_params(int &nvotes, int &margin, int &machineError) {
	cout << "\nEnter the total number of votes cast: " << flush;
	cin >> nvotes;
	filter_nvotes(nvotes);
	cout << "Enter the election margin percentage: " << flush;
	cin >> margin;
	filter_margin(margin);
	cout << "Enter voting machine error percentage: " << flush;
	cin >> machineError;
	filter_machineError(machineError);
	return;
}

void askToContinue(bool& carryOn) {
	char runAnother = 'N';
	cout << "\nDo you wish to Continue? (Y/n): " << flush;
	cin >> runAnother;
	runAnother = toupper(runAnother);
	while ((runAnother != 'Y') && (runAnother != 'N')) {
		cout << "Sorry but that was not recognized (Y/n): " << flush;
		cin >> runAnother;
		runAnother = toupper(runAnother);
	}
	if (runAnother == 'N') {
		carryOn = false;
	}
	else {
		carryOn = true;
	}
	return;
}

void loopy(int nvotes, int margin, int machineError, int votes[][2]) {
	bool carryOn = true;
	do {
		introduction();
		get_params(nvotes, margin,machineError);
		askToContinue(carryOn);
	} while (carryOn);
	return;
}

int main() {
	int nvotes = 0;
	int margin = 0;
	int machineError = 0;
	int votes[elections][2];
	loopy(nvotes, margin, error, votes);
	
	return 0;
}