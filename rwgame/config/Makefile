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
	rm testrunner

check:
	$(CC) $(CXXFLAGS) core.o config.o core_test.cc config_test.cc testrunner.cc $(LINK_TEST) -o testrunner
	./testrunner
