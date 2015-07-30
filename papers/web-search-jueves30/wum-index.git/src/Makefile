CPP=g++
CPPFLAGS=-Wall -std=c++0x  -O9 -DNDEBUG 
LIBS=../libcds/lib/libcds.a ../libs/trees.a 
# to compile tests /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread
INCLUDE_LIBCDS=../libcds/includes/
INCLUDE_TREES=../trees/

all: build_index testpredict experiments

test_lib:
	$(CPP) $(CPPFLAGS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES) -o test_lib test_lib.cpp $(LIBS)

tests:
	$(CPP) $(CPPFLAGS) -o test_sequence test_sequence.cpp $(LIBS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES)
	$(CPP) $(CPPFLAGS) -o test_ssa test_ssa.cpp $(LIBS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES)

build_index:
	$(CPP) $(CPPFLAGS) -o build_index build_index.cpp $(LIBS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES) -lpthread -fopenmp -I/home/rkonow/


testpredict:
	$(CPP) $(CPPFLAGS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES) -o testpredict testpredict.cpp $(LIBS) 

experiments:
	$(CPP) $(CPPFLAGS) -I$(INCLUDE_LIBCDS) -I$(INCLUDE_TREES) -o experiments experiments.cpp $(LIBS) 

clean:
	rm -f test_lib test_sequence test_ssa testpredict experiments build_index *.o