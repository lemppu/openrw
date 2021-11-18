CC = /usr/bin/c++

CXXFLAGS = -g -Wall -Werror -std=c++17

ROOT_DIR = ..

NOLINK = -c

LIBS = -lboost_system -lboost_program_options 

INCLUDE_DIRS = \
	$(ROOT_DIR)/rwcore

rwconfig.o: RWConfig.cpp
	$(CC) $(NOLINK) $(CXXFLAGS) -I$(INCLUDE_DIRS) $(LIBS) RWConfig.cpp -o RWConfig.o

clean:
	rm RWConfig.o
