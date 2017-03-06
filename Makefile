CC = g++
CXXFLAGS = -Wall -Wextra -pedantic
LIB = lib
OBJS = stack.o helper.o
DEPS = $(LIB)/stack.h $(LIB)/helper.h
EXES = gpushdir global_pop_dir

all: $(EXES)

gpushdir: gpushdir.o $(OBJS)
	$(CC) $(CXXFLAGS) gpushdir.o $(OBJS) -o gpushdir

global_pop_dir: gpopdir.o $(OBJS)
	$(CC) $(CXXFLAGS) gpopdir.o $(OBJS) -o global_pop_dir

gpushdir.o: gpushdir.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -c gpushdir.cpp

gpopdir.o: gpopdir.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -c gpopdir.cpp

stack.o:  stack.cpp $(LIB)/stack.h
	$(CC) $(CXXFLAGS) -c stack.cpp

helper.o: helper.cpp $(LIB)/helper.h
	$(CC) $(CXXFLAGS) -c helper.cpp

clean:
	rm *.o $(EXES)
