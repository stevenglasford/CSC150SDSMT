//   NAME: 
// Lab 8 - Pizza Deal Calculator
//  

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <stdlib.h>

using namespace std;

//complete the prototypes
void get_data(int& diameter, double& cost);
double calc_unit_cost(int diameter, double cost);
void show_deal(int bigDiameter, int smallDiameter, double bigCost, double smallCost);

/*The ONLY changes you will make to main()
* is adding function calls in the indicated
* positions. Do not make any other changes.
*/
int main()
{
	
	int lg_diam, sm_diam;
	double lg_cost, sm_cost;
	char movingOn = 'Y';
	bool carryOn = false;
	do {
		//Set output to 2 decimal places (money)
		cout << fixed << showpoint;
		cout << setprecision(2);

		//Print header
		cout << "Hardrocker Pizza Comparison Tool" << endl;
		cout << "--------------------------------" << endl << endl;

		cout << "Enter large pizza size & cost" << endl;
		//Get data for large pizza
		/*add function call here*/
		get_data(lg_diam, lg_cost);
		cout << endl;

		cout << "Enter small pizza size & cost" << endl;
		//Get data for small pizza
		/*add function call here*/
		get_data(sm_diam, sm_cost);
		cout << endl;

		//Show the details of the deal
		/*add function call here*/
		show_deal(lg_diam, sm_diam, lg_cost, sm_cost);
		
		cout << "Continue? (YN) " << flush;
		cin >> movingOn;
		movingOn = toupper(movingOn);
		while ((movingOn != 'Y') && (movingOn != 'N')) {
			cout << "\nSorry but that wasn't acceptable, continue (YN)" << flush;
			cin >> movingOn;
			movingOn = toupper(movingOn);
		}
		if (movingOn == 'Y') {
			carryOn = false;
		}
		else {
			carryOn = true; 
		}
		system("CLS");
	} while (!carryOn);
	return 0;
}

void get_data(int& diameter, double& cost) {
	cout << "Enter the price: " << flush;
	cin >> diameter;
	cout << "Enter the size: " << flush;
	cin >> cost;
}

double calc_unit_cost(int diameter, double cost) {
	return (cost / (M_PI * pow(static_cast<double>(diameter) / 2, 2)));
}

void show_deal(int bigDiameter, int smallDiameter, double bigCost, double smallCost) {
	double pricePerUnitLarge = calc_unit_cost(bigDiameter, bigCost);
	double pricePerUnitSmall = calc_unit_cost(smallDiameter, smallCost);

	cout << "\nLarge Pizza - " << bigDiameter << " inches at price $" <<
		fixed << setprecision(2) << bigCost << "\n\tcosts $" <<
		pricePerUnitLarge << " per square inch.";
	cout << "\nSmall Pizza - " << smallDiameter << " inches at price $" <<
		fixed << setprecision(2) << smallCost << "\n\tcosts $" <<
		pricePerUnitSmall << " per square inch." << endl;

	if (static_cast<int>(pricePerUnitLarge*1000) < static_cast<int>(pricePerUnitSmall*1000)) {
		cout << "\nThe larger pizza has a better deal" << endl;
	}
	else if (static_cast<int>(pricePerUnitLarge*1000) > static_cast<int>(pricePerUnitSmall*1000)) {
		cout << "\nThe small pizza has a better deal" << endl;
	}
	else {
		cout << "\nIt doesn't matter which pizza you get, they are "
			<< "basically the same price" << endl;
	}
}