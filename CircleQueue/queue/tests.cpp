#include <iostream>
using namespace std;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// This stops you using the built in queue
#define _GLIBCXX_QUEUE 1

#include "queue.h"
#include <deque>
#include <sstream>
using namespace std;

TEST_CASE("Constructor"){
	Queue *q = new Queue();
	GIVEN("A newly constructed queue"){
		THEN("It should be empty, not full, size = 0, and front = 0"){
			REQUIRE(q->size() == 0);
			REQUIRE(q->front() == 0);
			REQUIRE(q->is_empty());
			REQUIRE(!q->is_full());
		}
	}
}

TEST_CASE("Enqueue"){
	Queue *q = new Queue();
	INFO("This test checks that enqueueing & dequeueing returns the values in correct order");
	q->enqueue(1);
	q->enqueue(2);
	q->enqueue(3);
	q->enqueue(4);
	REQUIRE(q->dequeue() == 1);
	REQUIRE(q->dequeue() == 2);
	REQUIRE(q->dequeue() == 3);
	REQUIRE(q->dequeue() == 4);
	q->enqueue(5);
	REQUIRE(q->dequeue() == 5);
}

TEST_CASE("Front1"){
	Queue *q = new Queue();
	INFO("This test checks that the front accessor works corerctly");
	q->myFront = 2;
	REQUIRE(q->front() == 2);
}

TEST_CASE("Front2"){
	Queue *q = new Queue();
	INFO("This test checks that enqueueing & dequeueing updates front correctly");
	
	REQUIRE(q->front() == 0);
	q->enqueue(1);
	REQUIRE(q->front() == 0);
	q->enqueue(2);
	REQUIRE(q->front() == 0);

	q->dequeue();
	REQUIRE(q->front() == 1);
	q->enqueue(3);
	REQUIRE(q->front() == 1);
	q->enqueue(4);
	REQUIRE(q->front() == 1);
	
	q->dequeue();
	REQUIRE(q->front() == 2);

	q->enqueue(5);
	REQUIRE(q->front() == 2);	
	q->enqueue(6);
	REQUIRE(q->front() == 2);

	q->dequeue();
	REQUIRE(q->front() == 3);
	q->dequeue();
	REQUIRE(q->front() == 4);
	q->dequeue();
	REQUIRE(q->front() == 0);
	q->enqueue(7);
	q->enqueue(8);
	q->dequeue();
	REQUIRE(q->front() == 1);
}

TEST_CASE("Size1"){
	Queue *q = new Queue();
	INFO("This test checks that the size accessor works corerctly");
	q->mySize = 2;
	REQUIRE(q->size() == 2);
}

TEST_CASE("Size2"){
	Queue *q = new Queue();
	INFO("This test checks that enqueueing & dequeueing updates size correctly");
	REQUIRE(q->size() == 0);
	q->enqueue(1);
	REQUIRE(q->size() == 1);
	q->enqueue(1);
	REQUIRE(q->size() == 2);
	q->enqueue(1);
	REQUIRE(q->size() == 3);
	q->dequeue();
	REQUIRE(q->size() == 2);
	q->dequeue();
	REQUIRE(q->size() == 1);
	q->enqueue(1);
	REQUIRE(q->size() == 2);
}


TEST_CASE("Capacity1"){
	Queue *q = new Queue();
	INFO("This test checks that the capacity accessor works correctly");
	q->myCapacity = 3;
	REQUIRE(q->capacity() == 3);
}

TEST_CASE("Capacity2"){
	Queue *q = new Queue();
	INFO("This test checks that enqueueing & dequeueing updates capacity correctly");
	REQUIRE(q->capacity() == 5);
	for(int i = 0; i < 5; ++i){
		q->enqueue(i);	
		REQUIRE(q->capacity() == 5);
	}
	for(int i = 0; i < 5; ++i){
		q->enqueue(i);	
		REQUIRE(q->capacity() == 10);
	}
}
TEST_CASE("Printing"){
	INFO("This test adds some numbers to the queue and then prints - make sure you have a new line character at the enf of the print");
	Queue *q = new Queue();
	stringstream stream;
	q->enqueue(1);
	q->enqueue(2);
	q->enqueue(3);
	q->enqueue(4);
	q->print(stream);
	REQUIRE(stream.str() == "1,2,3,4\n");
}

TEST_CASE("full1"){
	INFO("This test adds some numbers (to the queue and checks is_full");
	Queue *q = new Queue();
	stringstream stream;
	q->enqueue(1);
	REQUIRE(!q->is_full());
	q->enqueue(2);
	REQUIRE(!q->is_full());
	q->enqueue(3);
	REQUIRE(!q->is_full());
	q->enqueue(4);
	REQUIRE(!q->is_full());
	q->enqueue(5);
	REQUIRE(q->is_full());
}

TEST_CASE("full2"){
	INFO("This test adds some numbers (enough to require a reallocation) to the queue and checks is_full");
	Queue *q = new Queue();
	stringstream stream;
	for(int i = 0; i < 4; ++i){
		q->enqueue(1);
		REQUIRE(!q->is_full());
	}
	// 5th enqueue makes it full
	q->enqueue(1);
	REQUIRE(q->is_full());

	for(int i = 0; i < 4; ++i){
		q->enqueue(1);
		REQUIRE(!q->is_full());
	}
	// 10th enqueue makes it full
	q->enqueue(1);
	REQUIRE(q->is_full());

	for(int i = 0; i < 9; ++i){
		q->enqueue(1);
		REQUIRE(!q->is_full());
	}
	// 20th enqueue makes it full
	q->enqueue(1);
	REQUIRE(q->is_full());
}

TEST_CASE("Reallocations"){
	INFO("This test checks that after reallocating, the queue is in the correct state");
	Queue *q = new Queue();
	
	q->enqueue(1); REQUIRE(q->front() == 0); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 1);
	q->enqueue(2); REQUIRE(q->front() == 0); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 2);
	q->enqueue(3); REQUIRE(q->front() == 0); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 3);
	q->enqueue(4); REQUIRE(q->front() == 0); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 4);
	q->dequeue();  REQUIRE(q->front() == 1); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 3);
	q->enqueue(5); REQUIRE(q->front() == 1); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 4);
	q->enqueue(6); REQUIRE(q->front() == 1); REQUIRE(q->capacity() == 5); REQUIRE(q->size() == 5);
	// Should reallocate
	q->enqueue(7); REQUIRE(q->front() == 0); REQUIRE(q->capacity() == 10); REQUIRE(q->size() == 6);
}

