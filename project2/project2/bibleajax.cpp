/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Bible.h"
#include "Verse.h"
#include "Ref.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  // Convert and check input data
  bool validInput = false;
  int chapterNum = 0;
  if (chapter != cgi.getElements().end()) {
	 chapterNum = chapter->getIntegerValue();
	 if (chapterNum > 150) {
		 cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
	 }
	 else if (chapterNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 validInput = true;
  }
  
  bool validVInput = false;
  int verseNum = 0;
  if (verse != cgi.getElements().end()) {
	 verseNum = verse->getIntegerValue();
	 if (verseNum > 176) {
		 cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
	 }
	 else if (verseNum <= 0) {
		 cout << "<p>The verse must be a positive number.</p>" << endl;
	 }
	 else
		 validVInput = true;
  }
  
  bool validBook = false;
  int bookNum = 0;
  string bookName = "Not real book";
  if (book != cgi.getElements().end()) {
	 bookNum = book->getIntegerValue();
	 if (bookNum > 66)
     {
		 cout << "<p>That book doesn't exist.</p>" << endl;
     }
	 else if (bookNum < 1)
	 {
		 cout << "<p>That book doesn't exist.</p>" << endl;
	 }
     else
     {
		 validBook = true;
		 bookName = bibleBooks[bookNum];
	 }
  }
  
  
  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */

  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */
	int bookToFind, chapToFind, verseToFind;
	bookToFind = book->getIntegerValue();
	chapToFind = chapter->getIntegerValue();
	verseToFind = verse->getIntegerValue();
	Ref refToFind = Ref(bookToFind, chapToFind, verseToFind);
	LookupResult status;
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	Verse findVerse = webBible.lookup(refToFind, status);
	string e = webBible.error(status);
	if (e == "Book doesn't exist.")
	{
		validBook = false;
		cout << "<b>" << e << "</b>" << endl;
	}
	else if (e == "Chapter doesn't exist.")
	{
		validInput = false;
		cout << "<b>" << e << "</b>" << endl;
	}
	else if (e == "Verse doesn't exist.")
	{
		validVInput = false;
		cout << "<b>" << e << "</b>" << endl;
	}
	else if (e == "Incorrect input.")
	{
		validBook = false;
		validInput = false;
		validVInput = false;
		cout << "<b>" << e << "</b>" << endl;
	}
  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */
  if (validInput && validVInput && validBook) {
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	cout << "<p>Your result: "
		 << bookName << " " << chapterNum << ":" << verseNum 
		 << "<em> " 
		 << findVerse.getVerse() << "</em></p>" << endl;
		 
    int numVerses = 1;
    if (nv != cgi.getElements().end())
    {
	  numVerses = nv->getIntegerValue();
	  if (numVerses > 1)				// if asked for more than 1 verse
		{
			for (int i = 0; i < numVerses - 1; i++)
			{
				findVerse = webBible.nextVerse(status);
				bookNum = findVerse.getRef().getBook();
				bookName = bibleBooks[bookNum];
				chapterNum = findVerse.getRef().getChap();
				verseNum = findVerse.getRef().getVerse();
				cout << bookName << " " << chapterNum << ":" << verseNum 
				<< "<em> " 
				<< findVerse.getVerse() << "</em></p>" << endl;
			}
		}
    }
  }
  
  return 0;
}
