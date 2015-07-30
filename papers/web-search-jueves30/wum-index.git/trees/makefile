CPP=g++
CPPFLAGS=-Wall -std=c++0x -O9 -DNDEBUG 
all:
	$(CPP) $(CPPFLAGS) -I./ -c *.cpp
	ar -rcs ../libs/trees.a *.o
	rm -rf *.o
