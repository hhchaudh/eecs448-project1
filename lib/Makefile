calendar.a: cmd_help.o
	ar rvs calendar.a cmd_help.o

cmd_help.o: cmd_help.cpp $(INC_DIR)/cmd_help.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c cmd_help.cpp

clean:
	rm *.o calendar.a || echo ------clean lib done------
