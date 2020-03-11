# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb
CXXFLAGS=-std=c++11 -pthread -g

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
pagetable : pagetable.o level.o main.o
	$(CXX) $(CXXFLAGS) -o pagetable $^

pagetable.o : map.h level.h pagetable.h pagetable.C

level.o : map.h level.h pagetable.h level.C

main.o : map.h level.h pagetable.h main.C

clean :
	rm *.o
