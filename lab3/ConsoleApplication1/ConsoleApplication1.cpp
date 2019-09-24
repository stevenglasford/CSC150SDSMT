#include <iostream>
#include <iomanip>
#include <cmath>



using namespace std;

int main() {
	int numPeople = 0;

	// Ask how many people there are 
	cout << "Enter the number of people: " << flush;
	cin >> numPeople;
	cout << " " << endl;

	// Ask how much money the group has
	double groupMoney = 0;
	cout << "Enter the amount of money the group has: " << flush;
	cin >> groupMoney;
	cout << " " << endl;

	// Ask for the price of the donuts
	double pricePerDonut = 0;
	cout << "Enter the price per donut: " << flush;
	cin >> pricePerDonut;
	cout << " " << endl;


	// convert the number of dollars to the number of cents
	
	// find the number of whole donuts
	int numDonuts = 0;
	numDonuts = static_cast<int>(groupMoney / pricePerDonut);

	// find the number of donuts per person
	int donutsPerPerson = 0;
	donutsPerPerson = numDonuts / numPeople;

	// find the number of left over donuts
	int donutsLeftOver = 0;
	donutsLeftOver = numDonuts % numPeople;

	// find the total cost of the whole donuts
	double totalDonutCost = 0;
	totalDonutCost = numDonuts * pricePerDonut;

	// find the amount of money left over from the donut purchase
	double moneyLeftOver = 0;
	moneyLeftOver = groupMoney - totalDonutCost;

	cout << "With $" << groupMoney << setprecision(2) << " you can purchase ";
	cout << numDonuts << " number of donuts and have $";
	cout << moneyLeftOver << setprecision(2) << " left over\n";
	cout << "Each person gets " << donutsPerPerson << " donuts and there will be " << donutsLeftOver << " donut/s left over" << endl;

	return 0;
}
