// NAME: STEVEN GLASFORD
// DATE: 29 AUGUST 2017
// ASSIGNMENT: CSC 150 LAB2


#include <iostream>
using namespace std;
int main() {
	cout << "*You ask for the number of items" << endl;
	cout << "\t*I input the number of items" << endl;
	cout << "*You save the number of items in your memory" << endl;
	cout << "*You then ask for the price of each item individually from me" << endl;
	cout << "*You stop asking for the price of the items after you have reached the number of items I gave you" << endl;
	cout << "*You add all the prices of the items together to get a subtotal" << endl;
	cout << "*The subtotal is then multiplied by the tax rate of .07 (7%), calculating a new total value and storing it your memory" << endl;
	cout << "*You determine which bracket this new total belongs to (free shipping, $5.99 shipping, etc.)" << endl;
	cout << "\t*If the total after tax is less than $20" << endl;
	cout << "\t\t*You add 0 dollars to the price of shipping" << endl;
	cout << "\t\t*Return to main activity" << endl;
	cout << "\t*If the total after taxes is greater than or equal to $20" << endl;
	cout << "\t\t*Store 5.99 dollars into your memory for the price of shipping" << endl;
	cout << "\t\t*Return to the main activity" << endl;
	cout << "\t*If the total after taxes is greater than or equal to $100" << endl; 
	cout << "\t\t*Multiply the subtotal after taxes by .1, then save this value to the price of shipping" << endl;
	cout << "\t\t*Return to the main activity" << endl;
	cout << "*Tell me the price I will need to pay for shipping" << endl;
	cout << "*Add the price of the shipping with the total price after taxes and print the resultant" << endl;
	cout << "*Stop thinking" << endl;
	return 0;
}