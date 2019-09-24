#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>


using namespace std;

int introduction() {
	int size = 0;
	cout << "Enter the number of route point: " << flush;
	cin >> size;
	cout << "Enter " << size << " different pairs in the format \"x y\"" << endl;
	return size;
}

//prints the final information
void summary(double totalDistance, double longX1, double longX2, double longY1,
	double longY2, double shortX1, double shortX2, double shortY1, 
	double shortY2, double longest, double shortest) {
	cout << fixed << setprecision(2) << "Total distance is " << totalDistance
		<< "\nLongest Segment is " << longest << ", between point (" <<
		longX1 << " ," << longY1 << ") and (" << longX2 << " ," << longY2
		<< ")\nShortest segment is " << shortest << ", between points ("
		<< shortX1 << " ," << shortY1 << ") and (" << shortX2 << " ,"
		<< shortY2 << ")" << endl;
	return;
}

void forPoints(int size) {
	double *xArray = new double[size];
	double *yArray = new double[size];
	double *distanceArray = new double[size - 1];
	double totalDistance = 0;
	double longestPointX1 = 0;
	double longestPointX2 = 0;
	double longestPointY1 = 0;
	double longestPointY2 = 0;
	double longestLength = 0;
	double shortestPointX1 = 0;
	double shortestPointX2 = 0;
	double shortestPointY1 = 0;
	double shortestPointY2 = 0;
	double shortest = 0;
	
	
	//store the points in the different arrays
	for (int i = 0; i < size; i++) {
		cin >> xArray[i] >> yArray[i];
	}
	//calculates the distances between the points and store them in the
	//	distance array
	//initializes the longest and shortest values for accurate information later on 
	distanceArray[0] = sqrt(pow(xArray[0] - xArray[1], 2) + pow(yArray[0] - yArray[1], 2));
	longestLength = distanceArray[0];
	shortest = longestLength;
	for (int i = 0; i < size - 1; i++) {
		//calculate the distances between points
		distanceArray[i] = sqrt(pow(xArray[i] - xArray[i + 1], 2) + pow(yArray[i] - yArray[i + 1], 2));
		//add up the distances and store in memory
		totalDistance += sqrt(pow(xArray[i] - xArray[i + 1], 2) + pow(yArray[i] - yArray[i + 1], 2));
		//find the largest information
		if (longestLength < distanceArray[i]) {
			longestLength = distanceArray[i];
			longestPointX1 = xArray[i];
			longestPointX2 = xArray[i + 1];
			longestPointY1 = yArray[i];
			longestPointY2 = yArray[i + 1];
		}
		//find the shortest information
		if (distanceArray[i] < shortest) {
			shortest = distanceArray[i];
			shortestPointX1 = xArray[i];
			shortestPointX2 = xArray[i + 1];
			shortestPointY1 = yArray[i];
			shortestPointY2 = yArray[i + 1];
		}
	}
	delete[] xArray;
	delete[] yArray;
	//This stuff is for debugging stuff
	/*
	for (int i = 0; i < size - 1; i++) {
		cout << "The distance between points " << i + 1 << " and " << i + 2 << " is: " << distanceArray[i] << endl;
	}
	*/
	delete[] distanceArray;
	summary(totalDistance, longestPointX1, longestPointX2, longestPointY1,
		longestPointY2, shortestPointX1, shortestPointX2, shortestPointY1,
		shortestPointY2, longestLength, shortest);
	return;
}

int main()
{
	int size = 0;
	size = introduction();
	forPoints(size);
	return 0;
}

