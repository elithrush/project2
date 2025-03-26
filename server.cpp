#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include "fifo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

int main() 
{
	string requestFifoName = "lookup_request";
	string replyFifoName = "lookup_reply";
    
	Fifo requestFifo(requestFifoName);
	Fifo replyFifo(replyFifoName);
    
	requestFifo.openread();
	replyFifo.openwrite();
		
    Bible bible;
    
    while (true) 
	{		
        string request = requestFifo.recv();
        if (request.empty()) continue;
        
        int book, chapter, verse, count = 1;
        istringstream iss(request);
        iss >> book >> chapter >> verse;
        if (!(iss >> count)) 
		{
			count = 1;
		}
        
        Ref ref(book, chapter, verse);
        LookupResult status;
        Verse verseText = bible.lookup(ref, status);
        
        if (status == SUCCESS) 
		{
            string response = verseText.getRef().getBookName().append(" ").append(to_string(verseText.getRef().getChap()).append(":").append(to_string(verseText.getRef().getVerse()).append(" ").append(verseText.getVerse())));
            replyFifo.send(response);
            
            for (int i = 1; i < count; i++) 
			{
                verseText = bible.nextVerse(status);
                if (status != SUCCESS) break;
                response = verseText.getRef().getBookName().append(" ").append(to_string(verseText.getRef().getChap()).append(":").append(to_string(verseText.getRef().getVerse()).append(" ").append(verseText.getVerse())));
                replyFifo.send(response);
            }			
        } 
		else 
		{
            replyFifo.send(bible.error(status));
        }
    }
	requestFifo.fifoclose();
	replyFifo.fifoclose();
    
    return 0;
}
