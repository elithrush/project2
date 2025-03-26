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

int lastPos;
// Constructor
Bible::Bible() 
{ 
	infile = "/home/class/csc3004/Bibles/web-complete";
	buildIndex();
}

Bible::Bible(string bib)
{
	infile = bib;
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
	
    instream.open(infile);
    instream.seekg(it->second);
    string line;
    getline(instream, line);
	Verse search(line);
	Ref foundRef = search.getRef();
	lastPos = instream.tellg();
	instream.close();
	
	if (ref.getBook() > 66)			// if book doesn't exist
		{
			status = NO_BOOK;
			return aVerse;
		}
		
		if (search.getRef() == ref)			// if the searched verse reference = the reference asked for
		{
			status = SUCCESS;
			return search;
		} 
		else if (foundRef.getBook() == ref.getBook() && ref.getChap() != foundRef.getChap())			// if chapter doesn't exist
		{
			status = NO_CHAPTER;
			return aVerse;
		}
		else if (foundRef.getBook() == ref.getBook() && foundRef.getChap() == ref.getChap() && ref.getVerse() != foundRef.getVerse())			// if verse doesn't exist
		{
			status = NO_VERSE;
			return aVerse;
		}
		else					// anything else
		{
			status = OTHER;
			return aVerse;
		}

    status = SUCCESS;
    return Verse(line);
	
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) 
{
	Verse next;
	string line2;
	
	instream.open(infile);
	
    instream.seekg(lastPos);
	
    if (getline(instream, line2)) 
	{
        next = Verse(line2);
        status = SUCCESS;
        lastPos = instream.tellg();
    } 
	else 
	{
        lastPos = 0; 
    }
	instream.close();
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
