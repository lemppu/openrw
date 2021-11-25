CC = /usr/bin/c++

CXXFLAGS = -g -std=c++20\
           -Wall -Werror -Wpedantic -Wdouble-promotion\
           -Wextra\
           --coverage

NOLINK = -c

LINK_TEST = -lCppUTest

all: iniparser.o argparser.o core.o config.o

iniparser.o: iniparser.cc
	$(CC) $(CXXFLAGS) $(NOLINK) iniparser.cc -o iniparser.o

argparser.o: argparser.cc
	$(CC) $(CXXFLAGS) $(NOLINK) argparser.cc -o argparser.o

core.o: core.cc
	$(CC) $(CXXFLAGS) $(NOLINK) core.cc -o core.o

config.o: config.cc
	$(CC) $(CXXFLAGS) $(NOLINK) config.cc -o config.o

clean:
	@rm -f *.o *.gcno *.gcda
	@rm -f testrunner

test: all
	@$(CC) $(CXXFLAGS) iniparser.o argparser.o core.o config.o\
        iniparser_test.cc argparser_test.cc core_test.cc config_test.cc\
        testrunner.cc $(LINK_TEST) -o testrunner
	@./testrunner

coverage: test
	@$(eval TEST_COVERAGE=$(shell\
        gcovr -d -f iniparser.cc -f argparser.cc -f config.cc -f core.cc |\
        sed -n '/^TOTAL/p' | awk '{ print $$4 }'))
	@$(eval LOC=$(shell\
        cloc . --include-lang=C++,"C/C++ Header" --not-match-f='test' |\
        sed -n '/^SUM/p' | awk '{ print $$5 }'))

check: clean coverage
	@echo Test coverage: $(TEST_COVERAGE) \| LoC: $(LOC)
