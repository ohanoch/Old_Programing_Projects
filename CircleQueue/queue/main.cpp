#include <iostream>
#include <string>
using namespace std;

#include "queue.h"

int main(){
	Queue q;

	cout << "size:\t  " << q.size() << endl;
	cout << "capacity: " << q.capacity() << endl;
	cout << "front:\t  " << q.front() << endl;
	cout << "empty:\t  " << std::boolalpha << q.is_empty() << endl;
	cout << "full:\t  " << std::boolalpha << q.is_full() << endl;
	cout << string(20, '#') << endl;
	for(int i = 0; i < 10; ++i){
		q.enqueue(i);

		cout << "size:\t  " << q.size() << endl;
		cout << "capacity: " << q.capacity() << endl; // on the 6th insertion, the capacity should double
		cout << "front:\t  " << q.front() << endl;
		cout << "empty:\t  " << std::boolalpha << q.is_empty() << endl;
		cout << "full:\t  " << std::boolalpha << q.is_full() << endl;
		q.print(cout);
		cout << string(20, '#') << endl;
	}

	q.print(cout); // should print 0,1,2,3,4,5,6,7,8,9 followed by a newline character.
}
