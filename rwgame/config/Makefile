CC = /usr/bin/c++

CXXFLAGS = -g -std=c++17 \
           -Wall -Werror -Wextra -Wpedantic -Wdouble-promotion

NOMAIN = -c

LINK_TEST = -lCppUTest

all: core.o config.o

core.o: core.cc
	$(CC) $(CXXFLAGS) $(NOMAIN) core.cc -o core.o

config.o: config.cc
	$(CC) $(CXXFLAGS) $(NOMAIN) config.cc -o config.o

clean:
	rm *.o
	rm config_test

check:
	$(CC) $(CXXFLAGS) config_test.cc config.o $(LINK_TEST) -o config_test
	./config_test
	$(CC) $(CXXFLAGS) core_test.cc core.o $(LINK_TEST) -o core_test
	./core_test
