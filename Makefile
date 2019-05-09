# Makefile for user_programs
# Copied iRRAM/examples/Makefile
# Assumes that the iRRAM, mpfr, gmp, m are installed globally.

prefix      = /usr/local
exec_prefix = ${prefix}

CC          = gcc
CFLAGS      = -g -O2
CPP         = gcc -E
# CPPFLAGS    =     -I${prefix}/include
CXX         = g++ -std=c++17
CXXCPP      = g++ -E -std=c++17
CXXFLAGS    = -g -O2
# LDFLAGS     = -Xlinker -rpath  -Xlinker ${exec_prefix}/lib
# LDLIBS      = -L${exec_prefix}/lib
LDLIBS      = -liRRAM -lmpfr -lgmp  -lm

OBJECTS = IntegralOnSU2.o IntegralOnR3.o IntegralOnR.o

IntegralOnSU2: IntegralOnSU2.o IntegralOnR3.o
	$(CXX) $(CXXFLAGS) $? -o $@ $(LDLIBS)

clean:
	rm $(OBJECTS) IntegralOnSU2

thread_test: CXXFLAGS += -pthread
