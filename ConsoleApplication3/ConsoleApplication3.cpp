#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;
const int elections = 500;

void beforeIntroduction() {
	cout << "This program simulates voting in 500 districts, where the actual" <<
		"\noutcome of the election should be exactly 50.5% for candidate A, \n" <<
		"and 49.5% for candidate B. This program will randomly produce an error\n" <<
		"dependent on the machine error given. This program will also ask for a \n" <<
		"margin of error, and will use this value to determine whether or not the\n" <<
		"program witnessed an error.\n" << endl;
}

void introduction() {
	cout << "Enter voting simulation parameters. All values must be " <<
		"positive\n and greater than 0. Margin and error are entered as" <<
		" percentages (do not use the % sign) \nand cannot exceed 100." << endl;
	return;
}

int reallyRandomNumber() {
	//got help for figuring out the nondeterministic generator from 
	//	some Windows documentation on-line
	chrono::high_resolution_clock::time_point before = chrono::high_resolution_clock::now();
	int choice = 0;
	int randomNumber = 0;
	random_device rd;
	//This uses the Mersenne twister 19937 generator to find a 
	//	good random number
	mt19937 f(rd());
	//This uses the Ranlux 48 generator to add entropy
	ranlux48 g(static_cast<int>(f()));
	//This uses the Knuth-B generator to add even more entropy
	knuth_b h(static_cast<int>(g()));
	//the default random number engine
	default_random_engine i(h());
	//the minimal standard minstd_rand generator
	minstd_rand j(i());
	//the minimal standard minstd_rand0 generator
	minstd_rand0 k(j());
	//the Ranlux 24 base generator
	ranlux24_base l(k());
	//the Ranlux 48 base generator
	ranlux48_base m(l());
	//the ranlux 24 generator
	ranlux24 randomly(static_cast<int>(m()));
	//returns a really random positive number
	choice = (static_cast<int>(chrono::duration_cast<chrono::nanoseconds>
		(chrono::high_resolution_clock::now() - before).count())) % 10;

	switch (choice) {
	case 0:
		randomNumber = rd();
		break;
	case 1:
		randomNumber = f();
		break;
	case 2:
		randomNumber = static_cast<int>(g());
		break;
	case 3:
		randomNumber = h();
		break;
	case 4:
		randomNumber = i();
		break;
	case 5:
		randomNumber = j();
		break;
	case 6:
		randomNumber = k();
		break;
	case 7:
		randomNumber = l();
		break;
	case 8:
		randomNumber = static_cast<int>(m());
		break;
	default:
		randomNumber = randomly();
		break;
	}
	return abs(randomNumber);
}

void filter_nvotes(int& nvotes) {
	while (nvotes < 1) {
		cout << "Please enter something else (you must enter something" <<
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
	return;
}


void get_params(int& nvotes, int& margin, int& machineError){
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

void calc_error(int votes[][2], int nvotes, int margin, int machineError) {
	int numError = 0;
	double ErrorValue = 0;
	for (int i = 0; i < elections; i++) {
		if (margin < abs(static_cast<int>(((votes[i][0] - .505 
		* static_cast<double(nvotes)) / (.505 * static_cast<double>
		(nvotes))) * 100))) {
			numError++;
		}
	}
	errorValue = (static_cast<double>(numError) / static_cast<double>(elections)) * 100;
	display_summary(nvotes,margin,machineError,numError,errorValue);
	return;
}

void display_summary(int nvotes, int margin, int machineError, int numError,double errorValue) {
	cout << "** Election Machine Summary **\n" << "\nNumber of votes: " << nvotes << "\nElection margin: " << margin << "%" << "\nMachine error rate: " << machineError << "%\n\n" << "For " << elections << " runs, " << numError << " incorrect elections occured, for an error rate of " << errorValue << "%\n" <<endl;
	return;

void voting(int votes[][2], int nvotes, int margin, int machineError) {
	int newProgress = 0;
	int oldProgress = 0;
	int votesForHilary = 0;
	int votesForDonald = 0;
	cout << "Simulating voting" << endl;
	for (int i = 0; i < elections; i++) {
		//for Hilary
		for (int j = 0; j < (static_cast<int>(nvotes * .505)); j++){
			votesForHilary++;
			//Randomly changes a vote for Hilary to a vote for Donald
			//	depending on the machineError value entered by the user
			if ((reallyRandomNumber() % 1000) < machineError * 10) {
				votesForDonald++;
			}
		}
		//for Donald
		for (int j = (static_cast<int>(nvotes * .505)); j < nvotes; j++) {
			votesForDonald++;
			//randomly changes a vote for Donald to a vote for Hilary
			//	depending on the machineError value entered by the user.
			if ((reallyRandomNumber() % 1000) < machineError * 10) {
				votesForHilary++;
			}
		}
		//print the progress of the run
		newProgress = i/nvotes;
		if (newProgress > oldProgress) {
			oldProgress = newProgress;
			cout << "\r" << oldProgress << "% complete." << flush;
		}
		//store the votes in the matrix
		votes[i][0] = votesForHilary;
		votes[i][1] = votesForDonald;
	}
	calc_error(votes,nvotes,margin,machineError);
	return;
}

void askToContinue(bool& carryOn) {
	char runAnother = 'N';
	cout << "\nDo you wish to Continue? (Y/N): " << flush;
	cin >> runAnother;
	runAnother = toupper(runAnother);
	while ((runAnother != 'Y') && (runAnother != 'N')) {
		cout << "Sorry but that was not recognized (Y/N): " << flush;
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
		get_params(nvotes,margin,machineError);
		voting(votes,nvotes,margin,machineError);
		askToContinue(carryOn);
	} while (carryOn);
	return;
}


int main() {
	int nvotes = 0;
	int margin = 0;
	int machineError = 0;
	int votes[elections][2];
	beforeIntroduction();
	loopy(nvotes,margin,machineError,votes);
	return 0;