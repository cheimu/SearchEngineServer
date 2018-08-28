#
# Copyright ©2018 Gaohong Liu.  All rights reserved.
# Name: Gaohong Liu
# Student#: 1561226
# Email: gaohol@uw.edu
#
# This Makefile compiles everything
#

CC = gcc
CFLAGS = -g -Wall -std=c11

# this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile.
all: ex5

ex5: Vector.o ex5.o
	$(CC) $(CFLAGS) -o $@ $^ 

ex5.o: ex5.c 
	$(CC) $(CFLAGS) -c $< 

Vector.o: Vector.c 
	$(CC) $(CFLAGS) -c $<

clean: 
	/bin/rm -f *.o *~ ex5


