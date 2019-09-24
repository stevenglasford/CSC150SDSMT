/*-------------------------------------------------------------------
Lab6_1.cpp

Program: Looper
Course: CSC150
Date: 10/19/10 revised sept. 2017
Description:
Bad loop control.  The loop should end when the counter
reaches 20.  You will find that the program just keeps
on going and going and going......

DEBUGGING TECHNIQUE
A technique used for debugging is to place cout statements
after a variable is modified. Since this program just keeps on
going, cout statements won't be very useful.  (Use ctrl-c to
stop it!) Step thru the program using the Debug options 'Run to
Cursor' and 'Step Over' to trace thru the program. Look for the
point where the loop should stop and determine why it doesn't.
Note that you can highlight the condition in the while()
statement, then hover your mouse over the highlighted text to
see what it evaluates to (true or false).  Correct the code
so it does stop at 7 loops/iterations with variable i still
increasing by 3 each step.


---------------------------------------------------------------------
Includes
---------------------------------------------------------------------*/
#include <iostream>
using namespace std;


int main()
{
	int loops = 1;
	int i = 0;

	while (i < 21)
	{
		cout << "Loop executed " << loops << " times." << endl;
		loops++;
		i += 3;
	}


	return 0;
}