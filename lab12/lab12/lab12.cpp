//lab 12 - Geometric figures from file
//Fall 2017

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

/*Complete function prototype for read_data*/
void read_data(int shapes[][2], ifstream& fin, int& numEntries);
double triangle(int a);
double square(int a);
double pentagon(int a);
double hexagon(int a);

int main()
{
	// Declare variables
	char inFileName[100];
	char outFileName[100];
	ifstream fin;
	ofstream fout;
	int numEntries = 0;
	double totalArea = 0;

	int size[50][2];

	
	



	//Ask the user to enter the name of the input file and the name of the output file, storing to the two cStrings.
	cout << "Enter an input file name: " << flush;
	cin.getline(inFileName, 100);
	cout << "Enter an output file name: " << flush;
	cin.getline(outFileName, 100);


	// Open the named input data file, if error occurs, display message and exit the program.
	fin.open(inFileName);
	if (!inFileName) {
		cout << "Sorry but that file does not exist" << endl;
		return 1;
	}


	// Pass opened file variable and the array to read_data function.
	read_data(size,fin,numEntries);
	


	// Read through each row of valid data in the array, 
	//		passing length value to correct function to calculate area.
	//		Add the returned value from the math function to the total area.
	for (int i = 0; i < numEntries; i++) {
		switch (size[i][0]) {
		case 3:
			totalArea += triangle(size[i][1]);
			break;
		case 4:
			totalArea += square(size[i][1]);
			break;
		case 5:
			totalArea += pentagon(size[i][1]);
			break;
		default:
			totalArea += hexagon(size[i][1]);
			break;
		}
	}



	// When all data processed, open named output file.
	//  If error occurs, display message and exit. Otherwise, write total area to file.
	fout.open(outFileName);
	if (!fout) {
		cout << "Sorry but that file does not exist, ending program now" << endl;
		exit(1);
	}
	else {
		fout << totalArea;
	}




	// Close all files when finished using them.

	fin.close();
	fout.close();

	return 0;
}

// Function receives the opened file variable and the 2D data array.
// In this function, read the entire data file, storing all values to the 2D integer array; 
//   return the number of figures(rows) read in.
void read_data(int shapes[][2], ifstream& fin, int& numEntries)
{	
	while ( fin >> shapes[numEntries][0]){
		fin >> shapes[numEntries][1];
		numEntries++;
	}
	cout << "Read in " << numEntries << " number of rows" << endl;
	
	return;
}

double triangle(int a)
{
	return sqrt(3) / 4.0 * pow(a, 2);
}

double square(int a)
{
	return a * a;
}

double pentagon(int a)
{
	return 1 / 4.0 * sqrt(5 * (5 + 2 * sqrt(5))) * pow(a, 2);
}

double hexagon(int a)
{
	return 3 * sqrt(3) / 2 * pow(a, 2);
}