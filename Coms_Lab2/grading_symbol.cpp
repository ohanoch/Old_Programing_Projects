//File: grading_symbol.cpp
//Student Name: Or Hanoch
//Student Number: 1501858

#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
	double grade=0;
	
	cout<<"input your grade: \n";
	cin>>grade;

	if(grade>=90)
	{
		cout<<"Your grade is: A++ \n";	
	}
	else if(grade>=80)
	{
		cout<<"Your grade is: A+ \n";	
	}
	else if(grade>=75)
	{
		cout<<"Your grade is: A \n";	
	}
	else if(grade>=70)
	{
		cout<<"Your grade is: B \n";	
	}
	else if(grade>=60)
	{
		cout<<"Your grade is: C \n";	
	}
	else if(grade>=50)
	{
		cout<<"Your grade is: D \n";	
	}
	else
	{
		cout<<"Your grade is: F \n";	
	}

	return (0);
}
