CC = /usr/bin/c++

CXXFLAGS = -g -std=c++17 \
           -Wall -Werror -Wextra -Wpedantic -Wdouble-promotion --coverage

NOMAIN = -c

LINK_TEST = -lCppUTest

all: core.o config.o

core.o: core.cc
	$(CC) $(CXXFLAGS) $(NOMAIN) core.cc -o core.o

config.o: config.cc
	$(CC) $(CXXFLAGS) $(NOMAIN) config.cc -o config.o

clean:
	rm *.o *.gcno
	rm testrunner

test: all 
	@$(CC) $(CXXFLAGS) core.o config.o core_test.cc config_test.cc testrunner.cc $(LINK_TEST) -o testrunner
	@./testrunner

coverage: test
	@$(eval TEST_COVERAGE=$(shell gcovr -d -f config.cc -f core.cc |sed -n '/^TOTAL/p' |awk '{ print $$4 }'))
	@$(eval LOC=$(shell cloc . --include-lang=C++,"C/C++ Header" --not-match-f='test' | sed -n '/^SUM/p' | awk '{ print $$5 }'))

check: clean coverage
	@echo Test coverage: $(TEST_COVERAGE), LoC: $(LOC)
