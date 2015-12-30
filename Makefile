all: gpushdir gpopdir 

gpushdir: gpushdir.o
	g++ gpushdir.o -o gpushdir

gpopdir: gpopdir.o
	g++ gpopdir.o -o global_pop_dir

gpushdir.o: gpushdir.cpp
	g++ -c gpushdir.cpp

gpopdir.o: gpopdir.cpp
	g++ -c gpopdir.cpp

clean:
	rm *o gpushdir global_pop_dir