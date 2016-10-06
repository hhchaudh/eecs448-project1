calendar.a: cmd_help.o cmd_view.o util.o
	ar rvs calendar.a cmd_help.o cmd_view.o util.o

cmd_help.o: cmd_help.cpp $(INC_DIR)/command.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c cmd_help.cpp

cmd_view.o: cmd_view.cpp $(INC_DIR)/command.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c cmd_view.cpp

util.o: util.cpp $(INC_DIR)/command.h
	g++ -std=c++11 -g -Wall -I$(INC_DIR) $(DEBUG) -c util.cpp

clean:
	rm *.o calendar.a || echo ------clean lib done------
