EXENAME = besmart
OBJS = main.o Bayes.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all : $(EXENAME)
$(EXENAME) : $(OBJS)
		$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp Bayes.h
		$(CXX) $(CXXFLAGS) main.cpp

Bayes.o : Bayes.cpp Bayes.h
		$(CXX) $(CXXFLAGS) Bayes.cpp

test : tests.o Bayes.o 
		$(LD) tests.o Bayes.o $(LDFLAGS) -o test

tests.o : tests/tests.cpp tests/catch.hpp Bayes.h 
		$(CXX) $(CXXFLAGS) tests/tests.cpp 