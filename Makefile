# Bibleajax program
# Bob Kasper, MVNU Computer Science
# updated January 2020 to use
# c++11 compiler option, current paths on cs.mvnu.edu

# This is a Makefile for the Bible web app demo program.
# Copy this directory to a location within your home directory. 
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs.mvnu.edu/class/csc3004/USER/
# and open the bibleajax.html link.

# TO DO: Must replace "username" by your username
USER=elithrush

# Use GNU C++ compiler with C++11 standard
CC=g++
CFLAGS=-std=c++11

all:	server client.cgi PutCGI PutHTML
#all: testreader

# TO DO: For bibleajax.cgi, add dependencies to include
# compiled classes from Project 1 to be linked into the executable program
client.cgi:	client.o fifo.o
		$(CC) $(CFLAGS) -o client.cgi client.o Bible.o Verse.o Ref.o fifo.o -lcgicc
		# -l option is necessary to link with cgicc library

# main program to handle AJAX/CGI requests for Bible references
client.o:	client.cpp fifo.h
		$(CC) $(CFLAGS) -c client.cpp

# TO DO: copy targets to build classes from Project 1:
# Bible.o, Ref.o, Verse.o

server: server.o Bible.o Ref.o Verse.o fifo.o
	$(CC) $(CFLAGS) -o server server.o Bible.o Ref.o Verse.o fifo.o

server.o: server.cpp Bible.h Ref.h Verse.h fifo.h
	$(CC) $(CFLAGS) -c server.cpp
	
# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp
	
fifo.o: fifo.cpp fifo.h 
	$(CC) $(CFLAGS) -c fifo.cpp 

PutCGI:	client.cgi
		chmod 755 client.cgi
		cp client.cgi /var/www/html/class/csc3004/$(USER)/cgi-bin

		echo "Current contents of your cgi-bin directory: "
		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML:
		cp bibleindex.html /var/www/html/class/csc3004/$(USER)

		echo "Current contents of your HTML directory: "
		ls -l /var/www/html/class/csc3004/$(USER)

clean:		
		rm *.o core client.cgi
#		rm -f *.o testreader