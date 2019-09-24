#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <iomanip>
#include <random>
#include <stdlib.h>


using namespace std;

const int rows = 10;
const int columns = 20;

double gen_rand();
void fill_array(double rawData[][columns]);
double find_min(double rawData[][columns], int row);
double find_max(double rawData[][columns], int row);
double find_mean(double rawData[][columns], int row);
double find_stdev(double rawData[][columns], int mean, int row);
void display_stats(double stats[][4]);

int main() {
	double rawData[rows][columns] = { NULL };
	double stats[rows][4] = { NULL };
	srand(100);
	fill_array(rawData);
	for (int i = 0; i < rows; i++) {
		stats[i][0] = find_min(rawData,i);
		stats[i][1] = find_max(rawData,i);
		stats[i][2] = find_mean(rawData,i);
		stats[i][3] = find_stdev(rawData,stats[i][2],i);
	}
	display_stats(stats);
	system("pause");
	return 0;
}

double gen_rand() {
	double num = 0;
	random_device rd;
	//srand(rd());
	num = rand() % 5 + 1;  //range 1 to 5 inclusive
	num += rand() / (double)RAND_MAX; //add fractional value
	return num;
}

void fill_array(double rawData[][columns]) {
	int temp = 0;
	srand(100);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			rawData[i][j] = gen_rand();
		}
	}
	return;
}

double find_min(double rawData[][columns], int row) {
	double temp = 0;
	
		temp = rawData[row][0];
		for (int j = 0; j < columns; j++) {
			if (rawData[row][j] < temp) {
				temp = rawData[row][j];
			}
		}

	return temp;
}

double find_max(double rawData[][columns], int row) {
	int temp = 0;
	
		temp = rawData[row][0];
		for (int j = 0; j < columns; j++) {
			if (rawData[row][j] > temp) {
				temp = rawData[row][j];
			}
		}
	return temp;
}



double find_mean(double rawData[][columns], int row) {
	
	double average = 0;
		average = 0;
		for (int j = 0; j < columns; j++) {
			average += rawData[row][j];
		}
		average /= columns;
	return average;
}

double find_stdev(double rawData[][columns], int mean, int row) {
	double stdev = 0;
		stdev = 0;
		for (int j = 0; j < columns; j++) {
			stdev += pow((mean - rawData[row][j]), 2.0);
		}
		stdev = sqrt(stdev / (columns - 1));
	return stdev;
}

void display_stats(double stats[][4]) {
	cout << "Showing Stats\n" << endl;
	cout << setw(10) << "RUN#" << setw(10) << "MIN" << setw(10) << "MAX" <<
		setw(10) << "MEAN" << setw(10) << "STDDEV" << endl;
	for (int i = 0; i < rows; i++) {
		cout << fixed << setprecision(4) << setw(10) << i + 1 << setw(10) <<
			stats[i][0] << setw(10) << stats[i][1] << setw(10) <<
			stats[i][2] << setw(10) << stats[i][3] << endl;
	}
	return;
}