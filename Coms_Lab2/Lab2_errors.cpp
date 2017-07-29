#include <iostream>
#include <cmath>
using namespace std;

// Takes a value and an error value and linearizes to x and y axes being ln(x) and ln(y)
int main(void)
{
	double value = 0.0;
	double temp = 0.0;
	double error = 0.0;
//	double topError=0.0;
//	double bottomError=0.0;
	int a=1;	

/*	while (a==1)
	{
		cout << "input value: \n";
		cin >> value;
		temp=value;
		cout << "input error: \n";
		cin >> error;

		value= log(value);
		topError = value - log(temp+error);
		bottomError = value - log(temp-error);
		cout<< "value is: " << value << endl << "top error is: " << topError << endl << "bottom error is: " << bottomError << endl;
		
		cout <<"continue \n";
		cin >> a;
	} */
	
	while (a==1)
	{
		cout << "input value: \n";
		cin >> value;
		temp=value;
		cout << "input error: \n";
		cin >> error;
		
		cout << "value is: " << value << " error is: " << error <<endl;

		value= (log(value+error)+ log(value-error))/2;
		cout << "value is: " << value << " error is: " << error <<endl;
		error = abs(value-log(temp+error));
		cout<< "value is: " << value << endl << "error is: " << error << endl;
		
		cout <<"continue \n";
		cin >> a;
	}

	return (0);
}

