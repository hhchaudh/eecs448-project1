DEBUG=

Calendar: main.o Node.o DoubleLinkedList.o ReadWrite.o
	g++ -std=c++11 -g -Wall $(DEBUG) main.o Node.o DoubleLinkedList.o ReadWrite.o -o Calendar
	rm *.o

main.o: main.cpp ReadWrite.h DoubleLinkedList.h Node.h
	g++ -std=c++11 -g -Wall $(DEBUG) -c main.cpp

Node.o: Node.cpp Node.h
	g++ -std=c++11 -g -Wall $(DEBUG) -c Node.cpp

DoubleLinkedList.o: DoubleLinkedList.cpp DoubleLinkedList.h Node.h
	g++ -std=c++11 -g -Wall $(DEBUG) -c DoubleLinkedList.cpp

ReadWrite.o: ReadWrite.cpp ReadWrite.h DoubleLinkedList.h Node.h
	g++ -std=c++11 -g -Wall $(DEBUG) -c ReadWrite.cpp

clean:
	rm *.o Calendar
	echo clean done
