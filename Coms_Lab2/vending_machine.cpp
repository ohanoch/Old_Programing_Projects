//File: grading_symbol.cpp
//Student Name: Or Hanoch
//Student Number: 1501858

#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
	int choice=0;

	cout<< "Choose beverage by number: \n1. Apple \n2. Juice  \n3. Coke \n4. Water \n5. Sprite \n";
	cin >> choice;

	if (choice>5 || choice < 1)
	{
		cout << "Error - choice was not valid, here is your money back\n";
	}

	return (0);
}
