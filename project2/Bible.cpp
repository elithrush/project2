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

// Constructor
Bible::Bible() 
{ 
	infile = "/home/class/csc3004/Bibles/web-complete";
	buildIndex();
}

void Bible::buildIndex() 
{
    ifstream file(infile);
    if (!file) 
	{
        cerr << "Error opening Bible file!" << endl;
        return;
    }

    string line3;
    int byteOffset = 0;
    
    while (getline(file, line3)) 
	{
        Ref ref(line3);
        index[ref] = byteOffset;
        byteOffset = file.tellg();
    }

    file.close();
}

int Bible::getOffset(const Ref& ref) 
{
    if (index.empty()) 
	{
        buildIndex();
    }

    auto it = index.find(ref);
    if (it != index.end()) 
	{
        return it->second;
    } 
	else 
	{
        return -1; // Not found
    }
}



//Ref Bible::getNextRef(const Ref& ref) 
//{
//    Ref nextRef = ref;
//    nextRef.increment();  // Increment book/chapter/verse
//    return nextRef;
//}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line that holds ref ...
    // update the status variable
	status = OTHER; // placeholder until retrieval is attempted
	// create and return the verse object
	Verse aVerse;   // default verse, to be replaced by a Verse object
	                // that is constructed from a line in the file.
					
	//get line, make into verse, compare created ref with ref to be found
	
	auto it = index.find(ref);
    if (it == index.end()) {
        status = NO_VERSE;
        return Verse();
    }

    instream.open(infile);
    if (!instream.is_open()) {
        status = OTHER;
        return Verse();
    }

    instream.seekg(it->second);
    string line;
    getline(instream, line);
    

    status = SUCCESS;
    return Verse(line);
	
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
