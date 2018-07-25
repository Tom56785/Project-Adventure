/*
Current compilation command for easy reference:

g++ -g -std=c++11 libs/pugixml/pugixml.cpp *.h *.cpp -o tarot
*/

#include <iostream>
#include <string>
#include <vector>

#include "dialogue.h"
#include "inventory.h"

#include "libs/pugixml/pugixml.hpp"

using std::cout;
using std::endl;
using std::cin;

void testfunc() {
    cout << "Hello from test function!" << endl;
}

int main(int argc, char **argv) {


    /*

    INVENTORY TESTING SECTION

    */

    Inventory inventory;

    Item test(0, 5, "Stick", "Cruelly torn from a tree.");

    cout << endl << test.name() << endl;
    cout << test.desc() << endl;

    cout << test.quantity << endl;

    test.quantity = 23;

    cout << test.quantity << endl;

    test.quantity += 3;

    cout << test.quantity << endl;

    test.quantity -= 8;

    cout << test.quantity << endl;

    test.quantity *= 2;

    cout << test.quantity << endl;

    test.quantity /= 3;

    cout << test.quantity << endl;

    if (test.quantity == 13) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    inventory.add_item(test);
    inventory.add_item(1, 1, "Box", "It's a cardboard box.");
    inventory.add_item(2, 0, "Car", "It's a decent car.", true);

    cout << inventory[89].name() << endl;
    cout << inventory[0].name() << ": " << inventory[0].quantity << endl;
    cout << inventory[1].name() << ": " << inventory[1].quantity << endl;
    cout << inventory[2].name() << ": " << inventory[2].quantity << endl;

    inventory.remove_item(1);
    cout << inventory[1].name() << ": " << inventory[1].quantity << endl;

    inventory.update();
    cout << inventory[2].name() << ": " << inventory[2].quantity << endl;


    cout << "\n\n DIALOGUE TREE\n" << endl;
    /*

    DIALOGUE TREE TESTING SECTION

    */

    std::vector<DialogueOption> cacheOptions; // a cache loosely holding every dialogue option
    // these options can then be referenced by the dialogue classes rather than copied to save memory

    // read the dialogue file(s) to get this data and then place it into the cache

    // TEMPORARILY //

    Character Player;
    Player.ID = 0;
    Player.name = "John";

    Character Jane(1, "Jane", 0, 0, 255);

    // INITIALISING DIALOGUE OPTIONS //
    DialogueOption hello;
    hello.ID = 1; // LEADS RIGHT BACK TO THE START, but skips the intro dialogue
    hello.leadsTo = 1;
    hello.text = "Hello";

    DialogueOption quit;
    quit.ID = 2;
    quit.leadsTo = 9;
    quit.text = "Goodbye";

    DialogueClass tempP;
    tempP.ID = 1;
    tempP.character = &Player; // this is the player's line
    tempP.subtitles = "Hello, how are you doing?";
    tempP.time = 4;
    hello.dialogue.push_back(tempP);

    // this is Jane's line in response
    DialogueClass tempJ(2, &Jane, "I\'m fine. How about you?", 3);
    hello.dialogue.push_back(tempJ);

    hello.dialogue.push_back(DialogueClass(3, &Player, "Pretty good. What brings you here?", 3));
    hello.dialogue.push_back(DialogueClass(4, &Jane, "I found something in the river.", 3));
    hello.dialogue.push_back(DialogueClass(5, &Jane, "I wondered if you knew anything about it.", 5));
    hello.dialogue.push_back(DialogueClass(6, &Player, "Let's have a look.", 3));
    hello.dialogue.push_back(DialogueClass(7, &Player, "Now that is interesting.", 3));
    hello.dialogue.push_back(DialogueClass(8, &Jane, "What should we do with it?", 4));

    quit.dialogue.push_back(DialogueClass(1, &Player, "Goodbye.", 3));
    quit.dialogue.push_back(DialogueClass(2, &Jane, "See you later.", 3));

    // adding these options to the cache
    cacheOptions.push_back(hello);
    cacheOptions.push_back(quit);

    // create the INTRODUCTION dialogue tree

    DialogueTree intro;
    DialogueScreen intro_0p; // passive first screen, just dialogue
    DialogueScreen intro_1;

    // setup the introductory passive screen
    intro_0p.ID = 0;
    intro_0p.passive = true;

    DialogueOption empty(1, 1, "");
    empty.dialogue.push_back(DialogueClass(1, &Player, "Welcome to Tarot!", 3, testfunc));
    empty.dialogue.push_back(DialogueClass(2, &Jane, "We hope you have a good stay!", 4));
    intro_0p.options.push_back(empty);

    // setup the first options screen
    intro_1.ID = 1;
    intro_1.options.push_back(hello);
    intro_1.options.push_back(quit);

    // setup the master tree
    intro.ID = 1;
    intro.screens.push_back(intro_0p);
    intro.screens.push_back(intro_1);

    //////////////////


    // RUN the dialogue tree
    intro.run();



    /*

    PugiXML Testing section

    */


    // create the XML document (in memory)
    pugi::xml_document doc;

    // load the file and save the result
    pugi::xml_parse_result result = doc.load_file("../cd_catalog.xml");

    cout << "\nXML Loading Result: " << result.description() << endl;

    // load the CD node
    pugi::xml_node cd = doc.child("CATALOG");

    // display all of its data
    for (pugi::xml_node c = cd.first_child(); c; c = c.next_sibling()) {
        cout << "CD:";
        // display all the child nodes which contain info about the CDs
        for (pugi::xml_node n = c.first_child(); n; n = n.next_sibling()) {
            cout << " " << n.name() << ": " << n.text().as_string();
        }
        cout << endl;
    }

    return 0;
}
