#include <iostream>
#include <cmath>

using namespace std;

int main (void)
{
	double l=0;
	double l_error=0;
	double v=0;
	double v_error=0;
//	double m=0;
//	double m_error=0;
	double t=0;
//	double momentum=0;
//	double momentum_error=0;
//	double ke=0;
//	double ke_error=0;
	//double more=1;

	cout << "enter length: \n";
	cin >> l;
	cout << "enter length error: \n";
	cin >> l_error;
//	cout << "enter mass: \n";
//	cin >> m;
//	cout << "enter mass: \n";
//	cin >> m_error;

	while (true)
	{
		cout << "enter time: \n";
		cin >> t;
		
		v=l/t;
		v_error=l_error/t;

//		momentum=v*m;
//		momentum_error=v_error*m+m_error*v;

//		ke=0.5*m*v*v;
//		ke_error=0.5*((v_error*v*2)*m+m_error*v*v);

		cout << "velocity = " << v << " +- " << v_error << endl; 
		cout << "velocity squared = " << v*v << " +- "<< v_error*v*2 << endl;
	//	cout << "momentum = " << momentum << " +- " << momentum_error << endl; 
	//	cout << "kinetic energy = " << ke << " +- " << ke_error << endl; 

		//cout << "continue? (1/0)" << endl;
		//cin >> more;
	}

	return 0;

}
