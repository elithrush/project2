// Class Bible
// Computer Science, MVNU
//
// A Bible object represents a particular version of the Bible,
// and provides functions to lookup verses and references.
// A Bible object is constructed by giving it a file name string 
// that refers to a file containing the entire text of a version.

#ifndef Bible_H
#define Bible_H

#include "Ref.h"
#include "Verse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

// status codes to be returned when looking up a reference
enum LookupResult { SUCCESS, NO_BOOK, NO_CHAPTER, NO_VERSE, OTHER };

class Bible {	// A class to represent a version of the bible
 private:
   string infile;		// file path name
   ifstream instream;	// input stream, used when file is open
   bool isOpen;			// true if file is open
   // OPTIONAL: you may add variables to keep track of
   // the current line and/or reference when scanning the file
   
   map <Ref, int> index;
   int lastPos;
   
 public:
   Bible();	// Default constructor
   Bible(string bib);
   
   // REQUIRED: Find and return a verse in this Bible, given a reference
   Verse lookup(const Ref ref, LookupResult& status);
   // REQUIRED:
   // Return the next verse from the Bible file stream if the file is open.
   // If the file is not open, open the file and return the first verse.
   Verse nextVerse(LookupResult& status);
   
   int getOffset(const Ref& ref);
   
   Ref getNextRef(const Ref& ref);
   
   // Information functions (REQUIRED)
   // Return an error message string to describe status
   string error(LookupResult status);
   // Show the name of the bible file on cout
   void display();
   
   void buildIndex();
   int getIndexSize() const { return index.size(); }
   int getLastOffset() const { return index.empty() ? -1 : index.rbegin()->second; }
   int getOffsetForRef(const Ref& ref) const {
        auto it = index.find(ref);
        return (it != index.end()) ? it->second : -1;
   }
   // OPTIONAL: Return the reference after the given parameter ref
   Ref next(const Ref ref, LookupResult& status);
   // OPTIONAL: Return the reference before the given parameter ref
   Ref prev(const Ref ref, LookupResult& status);
};
#endif //Bible_H
