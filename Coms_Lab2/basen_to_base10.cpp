//File basen_to_base10.cpp
//Student Name: Or Hanoch
//Student Number: 1501858
#include <iostream>
#include <cmath>
using namespace std;

// the rows put as comments are another way of implementing this function, but are longer.
int main(void)
{
	int num=0;
	int base=0;
	int new_num=0;
//	int temp=0;

	cout << " enter 4 digit numnber \n";
	cin >> num;
	cout << "enter the base you are using\n";
	cin >> base;
//	temp=num;

//	new_num=temp%10;
//	temp=temp/10;
//	new_num=new_num+(temp%10)*base;
//	temp=temp/10;
//	new_num=new_num+(temp%10)*pow(base,2);
//	temp=temp/10;
//	new_num=new_num+(temp%10)*pow(base,3);

	new_num=(num/1000)*pow(base,3)+((num/100)%10)*pow(base,2)+((num/10)%10)*base+num%10;
	
	cout << "Your number in base 10 is: " << new_num << endl;

	return (0);
}

