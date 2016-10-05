Calendar: main.o Node.o DoubleLinkedList.o ReadWrite.o Detail.o $(LIB_DIR)/calendar.a
	g++ -std=c++11 -g -Wall $(DEBUG) main.o Detail.o Node.o DoubleLinkedList.o ReadWrite.o $(LIBS) -o Calendar

main.o: main.cpp $(INC_DIR)/calendar_std.h $(INC_DIR)/command.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c main.cpp

Node.o: Node.cpp $(INC_DIR)/Node.h $(INC_DIR)/Detail.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c Node.cpp

Detail.o: Detail.cpp $(INC_DIR)/Detail.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c Detail.cpp

DoubleLinkedList.o: DoubleLinkedList.cpp $(INC_DIR)/DoubleLinkedList.h $(INC_DIR)/Node.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c DoubleLinkedList.cpp

ReadWrite.o: ReadWrite.cpp $(INC_DIR)/ReadWrite.h $(INC_DIR)/DoubleLinkedList.h $(INC_DIR)/Node.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c ReadWrite.cpp

clean:
	rm *.o Calendar || echo ------clean calendar done------
