DEBUG=
INC_DIR = ../includes
LIB_DIR = ../lib
LIBS = $(LIB_DIR)/calendar.a
export

MAIN:
	cd lib && $(MAKE)
	cd calendar && $(MAKE)
	cp calendar/Calendar Calendar

clean:
	cd lib && $(MAKE) clean
	cd calendar && $(MAKE) clean
	rm Calendar || echo ------clean done------
