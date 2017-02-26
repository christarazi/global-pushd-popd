CC = g++
OBJS = stack.o helper.o
DEPS = stack.h helper.h
EXES = gpushdir global_pop_dir

all: $(EXES)

gpushdir: gpushdir.o $(OBJS)
	$(CC) gpushdir.o $(OBJS) -o gpushdir

global_pop_dir: gpopdir.o $(OBJS)
	$(CC) gpopdir.o $(OBJS) -o global_pop_dir

gpushdir.o: gpushdir.cpp $(DEPS)
	$(CC) -c gpushdir.cpp

gpopdir.o: gpopdir.cpp $(DEPS)
	$(CC) -c gpopdir.cpp

stack.o:  stack.cpp stack.h
	$(CC) -c stack.cpp

helper.o: helper.cpp helper.h
	$(CC) -c helper.cpp

clean:
	rm *.o $(EXES)
