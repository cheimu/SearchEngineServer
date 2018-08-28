#
# Copyright ©2018 Gaohong Liu.  All rights reserved.
# Name: Gaohong Liu
# Student#: 1561226
# Email: gaohol@uw.edu
#
# This Makefile compiles everything
#

CXX = g++
CFLAGS = -g -Wall -std=c++11

# this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile.
all: ex9

ex9: IntPair.o ex9.o
	$(CXX) $(CFLAGS) -o $@ $^ 

%.o: %.cc 
	$(CXX) $(CFLAGS) -c $< 

clean: FORCE
	/bin/rm -f *.o *~ ex9

FORCE:
