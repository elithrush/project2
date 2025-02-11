// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line that holds ref ...
    // update the status variable
	status = OTHER; // placeholder until retrieval is attempted
	// create and return the verse object
	Verse aVerse;   // default verse, to be replaced by a Verse object
	                // that is constructed from a line in the file.
					
	//get line, make into verse, compare created ref with ref to be found
	if (!instream.is_open())
	{
		instream.open(infile, ifstream::in);
	}
	string line;
	Verse search;
	
	if (ref.getBook() > 66)			// if book doesn't exist
		{
			status = NO_BOOK;
			return aVerse;
		}
		
	while (!instream.eof())			// while it's not the end of the Bible file
	{
		getline(instream, line);
		search = Verse(line);
		
		if (search.getRef() == ref)			// if the searched verse reference = the reference asked for
		{
			status = SUCCESS;
			return search;
		} 
		else if (ref.getBook() < search.getRef().getBook())			// if chapter doesn't exist
		{
			status = NO_CHAPTER;
			return aVerse;
		}
		else if (ref.getChap() < search.getRef().getChap() && ref.getBook() == search.getRef().getBook())			// if verse doesn't exist
		{
			status = NO_VERSE;
			return aVerse;
		}
		else					// anything else
		{
			status = OTHER;
		}
	}
    return(aVerse);
	
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) 
{
	Verse next;
	string line2;
	if (!instream.is_open())			// error handling
	{
		instream.open(infile, ifstream::in);
		next = Verse("1 1 1");
		status = SUCCESS;
		return next;
	}
	getline(instream, line2);
	next = Verse(line2);
	status = SUCCESS;
	return next;
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) 
{
	string error = "No error!";
	if (status == NO_BOOK)
	{
		error = "Book doesn't exist.";
		return error;
	}
	else if (status == NO_CHAPTER)
	{
		error = "Chapter doesn't exist.";
		return error;
	}
	else if (status == NO_VERSE)
	{
		error = "Verse doesn't exist.";
		return error;
	}
	else if (status == OTHER)
	{
		error = "Incorrect input.";
		return error;
	}
	return error;
}

void Bible::display() 
{
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) 
{
	return ref;
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) 
{
	return ref;
}
