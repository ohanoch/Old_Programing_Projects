#include <iostream>
#include <string>
using namespace std;

class Queue{
public:
	// Constructor: Allocate some initial capacity of 5 items
	//   remember to initialise all class variables
	Queue(){
		myData = new int[5];
		// initialise all the other variables...
        myCapacity=5;
        myFront=0;
        mySize=0;
	}
	// Destructor: Free the allocated memory
	~Queue(){
		delete[] myData;
	}

	// Get the index of the front item
	int front() const{
        return myFront;

	}
	// Get the number of items in the queue
	int size() const{
        return mySize;
	}
	// Get the capacity of the array
	int capacity() const{
        return myCapacity;
	}
	// Is the queue full?
	bool is_full() const{
        return mySize/myCapacity;
	}
	// Is the queue empty?
	bool is_empty() const{
        return mySize==0;
	}
	// Reallocate the underlying array
	//   allocate 2*capacity
	//   copy all the items into the new array, the front index
	//     in the new array should be 0
	//   free the old array
	void reallocate_and_copy(){
        myCapacity=myCapacity*2;
        int* temp=new int[myCapacity];
        for (int i=0; i<myCapacity/2; i++)
        {
            temp[i]=myData[myFront+i];
        }
        myFront=0;
        delete myData;
        myData=temp;
	}

	// Add a value to the queue
	void enqueue(int value){
		if(is_full()){
			reallocate_and_copy();
		}
		// Do more stuff here...
        myData[(myFront+mySize)%myCapacity]=value;
        mySize++;
	}
	// Remove and return the front value from the queue
	int dequeue(){
        myFront=(myFront+1)%myCapacity;
        mySize--;
        return myData[(myFront+myCapacity-1)%myCapacity];
	}
	// Print the values in the queue starting at front
	//   only print the values in the queue, not empty spaces
	//   eg: 1,2,3,4,5,6
	// I will never call this on an empty list
	void print(std::ostream &out) const{
       for(int i=0; i<mySize-1; i++){
           out<<myData[(myFront+i)%myCapacity]<<",";
       }
       out<<myData[(myFront+mySize-1)%myCapacity]<<endl;
	}

public:
	// Class variables
	int *myData;
	int myCapacity;
	int myFront;
	int mySize;
};

