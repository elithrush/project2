#include <iostream>
#include <cstdlib>
#include "Bible.h"
#include "Ref.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 4) 
	{
        cerr << "Not enough arguments." << endl;
        return 1;
    }
	else if (argc > 5)
	{
		cerr << "Too many arguments." << endl;
        return 1;
	}

    string bibleFile = "/home/class/csc3004/Bibles/web-complete";
    Bible bible(bibleFile);
	
    if (argc > 3) 
	{
        cout << "Total verses indexed: " << bible.getIndexSize() << endl;
        cout << "Last verse indexed at byte offset: " << bible.getLastOffset() << endl;
		
        int book = stoi(argv[1]);
        int chapter = stoi(argv[2]);
        int verse = stoi(argv[3]);
        int count = 1;
		if (argc == 5)
		{
			count = stoi(argv[4]);
		}

        Ref ref(book, chapter, verse);

        for (int i = 0; i < count; ++i) 
		{
            string verseText = bible.lookup(ref, status);
            
            if (!verseText.empty()) 
			{
                cout << ref << " - " << verseText << endl;
                ref = ref.next();
            } 
			else 
			{
                cout << "Verse not found for " << ref << "!" << endl;
                break;
            }
        }
    } 
	else 
	{
        cerr << "Invalid arguments. Provide either no extra arguments or a full reference: (book chapter verse [count])." << endl;
        return 1;
    }

    return 0;
}
