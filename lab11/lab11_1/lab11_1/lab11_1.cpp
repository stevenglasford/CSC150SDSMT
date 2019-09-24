#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <stdlib.h>



using namespace std;

void abbr_subject(char fullname[], char abbrname[]) {
	abbrname[0] = toupper(fullname[0]);
	int letters = 1;
	for (int i = 1; i < strlen(fullname); i++) {
		if (isspace(fullname[i])) {
			abbrname[letters] = toupper(fullname[i + 1]);
			letters++;
		}
	}
	return;
}

void compute_hours(char abbrname[], int& numCourses,  double& major, double& other) {
	cout << "Enter the number of courses you have taken: " << flush;
	double credit_hours = 0;
	cin >> numCourses;
	char temp[100] = { 0 };
	for (int i = 0; i < numCourses; i++) {

		for (int j = 0; j < 100; j++) {
			temp[j] = '\0';
		}
		credit_hours = 0;
		cout << "Enter course #" << i + 1 << ": " << flush;
		cin.getline(temp, 100);
		cin.ignore(100,'\n');

		cout << "Enter credit hours #" << i + 1 << ": " << flush;
		cin >> credit_hours;
		other += credit_hours;
		for (int j = 0; j < 20; j++) {
			if (isalpha(temp[j])) {
				temp[j] = toupper(temp[j]);
			}
		}
		if (strncmp(abbrname, temp, 2)) {
			major += credit_hours;
		}
	}

	return;
}

void display(double major, double other, char abreviated[]) {
	cout << "\n" << abreviated << " major credits hours: " << major;
	cout << "\nTotal credit hours: " << other << endl;
}

int main() {
	char major[100] = { 0 };
	char abreviated[100] = { 0 };
	int numCourses = 0;
	double majorCourses = 0;
	double other = 0;

	cout << "Enter your Major: " << flush;
	cin.getline(major, 100);

	abbr_subject(major, abreviated);
	cout << "Abbreviation: " << abreviated << endl;

	compute_hours(abreviated,numCourses, majorCourses, other);

	display(majorCourses, other, abreviated);
	system("pause");
	return 0;
}

