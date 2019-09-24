#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>


using namespace std;

void abbr_subject(char fullname[],char abbrname[]) {
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

int main() {
	char major[100] = { 0 };
	char abreviated[100] = { 0 };

	cout << "Enter your Major: " << flush;
	cin.getline(major, 100);

	abbr_subject(major, abreviated);
	cout << "Abbreviation: " << abreviated << endl;


    return 0;
}

