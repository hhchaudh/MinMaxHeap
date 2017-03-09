lab7: main.o PrecondViolatedExcep.o MinMaxHeap.o
	g++ -std=c++11 -g -Wall main.o PrecondViolatedExcep.o MinMaxHeap.o -o lab7

main.o: QNode.h QNode.hpp Queue.h Queue.hpp main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.h PrecondViolatedExcep.cpp
	g++ -std=c++11 -g -Wall -c PrecondViolatedExcep.cpp
    
MinMaxHeap.o: MinMaxHeap.h MinMaxHeap.cpp
	g++ -std=c++11 -g -Wall -c MinMaxHeap.cpp

clean:
	rm *.o lab7
	echo clean done