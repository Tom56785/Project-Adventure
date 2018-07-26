/*

XML Tarot Dialogue Writer

This program is a helper program for use in writing the XML files
for the dialogue in the game Tarot. This is much quicker than writing
them by hand and reduces the amount of human error.


MIT License

Copyright (c) 2018 Thomas Albans

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <climits>
#include <string>
#include <vector>

#include "../libs/pugixml/pugixml.hpp"


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;


#ifdef _WIN32 || _WIN64
static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif


int get_int();
void clear_screen();


int main(int argc, char** argv) {


    const string mainMenu = "XML Tarot Dialogue Writer\nCopyright (c) 2018 Thomas Albans\nLicensed under MIT License, license included with this software\n\n";

    // create the XML document and a Root node
    pugi::xml_document xml;

    //auto declarationNode = xml.append_child(pugi::node_declaration);
    //declarationNode.append_attribute("version")    = "1.0";
    //declarationNode.append_attribute("encoding")   = "ISO-8859-1";
    //declarationNode.append_attribute("standalone") = "yes";

    auto root = xml.append_child("Tarot");


    char choice = 0;
    bool first = true;

    do {

        if (!first) {
            clear_screen();
        } else {
            first = false;
        }

        cout << mainMenu << endl;

        cout << "1. Create Dialogue Tree" << endl;
        cout << "2. Save XML file" << endl;
        cout << "9. Quit without saving" << endl;

        cout << "\nOption: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1': {

                cout << "\nEnter ID: ";
                int ID = get_int();
                cout << "Enter root ID: ";
                int rt = get_int();

                // create the DialogueTree
                auto dTree = root.append_child("DialogueTree");
                dTree.append_attribute("ID") = ID;
                dTree.append_attribute("root") = rt;

                int c = 0;
                do {

                    // create the Dialogue Screens
                    clear_screen();
                    cout << mainMenu << endl;

                    cout << "1. Create Dialogue Screen" << endl;
                    cout << "2. Go back" << endl;

                    cout << "\nOption: ";
                    c = get_int();

                    if (c == 1) {
                        // create a new DialogueScreen
                        cout << "\nEnter ID: ";
                        ID = get_int();

                        char pass = 0;
                        while (pass != 'y' && pass != 'Y' && pass != 'n' && pass != 'N') {
                            cout << "Passive (y or n): ";
                            cin >> pass;
                            cin.ignore();
                        }
                        bool bPass = false;
                        if (pass == 'y' || pass == 'Y') {
                            bPass = true;
                        }

                        // write this data to the current Tree
                        auto dScreen = dTree.append_child("DialogueScreen");
                        dScreen.append_attribute("ID") = ID;
                        dScreen.append_attribute("passive") = bPass;


                        int o = 0;
                        do {
                            // create DialogueOptions
                            clear_screen();
                            cout << mainMenu << endl;

                            cout << "1. Create Dialogue Option" << endl;
                            cout << "2. Go back" << endl;

                            cout << "\nOption: ";
                            o = get_int();

                            if (o == 1) {
                                // create a new DialogueOption
                                cout << "\nEnter ID: ";
                                ID = get_int();

                                cout << "Leads to (ID of Screen): ";
                                int lTo = get_int();

                                cout << "Option text: ";
                                string txt;
                                getline(cin, txt);

                                // write this data into the current Screen
                                auto dOption = dScreen.append_child("DialogueOption");
                                dOption.append_attribute("ID") = ID;
                                dOption.append_attribute("leadsTo") = lTo;
                                dOption.append_attribute("text") = txt.c_str();

                            }


                        } while (o != 2);


                    }

                } while (c != 2);


                break;
            }
        case '2': {
                cout << "Enter filename: ";
                string name;
                getline(cin, name);
                xml.save_file(name.c_str());
                break;
            }
        }



    } while (choice != '9');


    return 0;
}

int get_int() {
    // function to retrieve an integer from input with error checking
    int inp;
    bool fail = false;

    do {
        fail = false;
        cin >> inp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            fail = true;
            cout << "Try again: ";
        }
    } while (fail);
    cin.ignore();

    return inp;
}

void clear_screen() {
#ifdef _WIN32 || _WIN64
	static COORD tl = { 0, 0 };
	static CONSOLE_SCREEN_BUFFER_INFO s;
	GetConsoleScreenBufferInfo(console, &s);
	static DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
#else
	write(1, "\E[H\E[2J", 7);
#endif
}

/*

Data needed to be stored in XML:

--DialogueTree  <-- this is the master tree, could be one per file or more than one
  {
    --ID
    --root (starting position)
    --DialogueScreen data
  }

--DialogueScreen  <-- each screen for the dialogue, displays all the options to the player
  {
    --ID
    --passive (whether this screen is passive)
    --DialogueOption data
  }

--DialogueOption  <-- each individual selectable option for the player
  {
    --ID
    --leadsTo (the ID of the screen this option leads to)
    --text (the text for the actual option)
    --DialogueClass data
  }

--DialogueClass  <-- each individual line of dialogue
  {
    --ID
    --character (who says the line, can't store all info just use character ID)
    --subtitles (the actual line of dialogue to be shown on screen)
    --time (amount of time to show the dialogue, float in seconds)
    --breakaway (function pointer if there is one, store as an index pointing to an array containing all breakaway functions)
  }




*/
