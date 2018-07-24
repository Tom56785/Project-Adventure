#include <iostream>
#include <string>
#include <vector>

#include "dialogue.h"
#include "inventory.h"

using std::cout;
using std::endl;
using std::cin;

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


    cout << "\n\n DIALOGUE TREE" << endl;
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

    // INITIALISING A SINGLE DIALOGUE OPTION //
    DialogueOption temp;
    temp.ID = 1;
    temp.leadsTo = 3;
    temp.text = "Hello";

    DialogueClass tempP;
    tempP.ID = 1;
    tempP.character = &Player; // this is the player's line
    tempP.subtitles = "Hello, how are you doing?";
    tempP.time = 4;
    temp.dialogue.push_back(tempP);

    // this is Jane's line in response
    DialogueClass tempJ(2, &Jane, "I\'m fine. How about you?", 3);
    temp.dialogue.push_back(tempJ);

    //////////////////

    // adding this option to the cache
    cacheOptions.push_back(temp);

    // output the entire contents of the CACHE
    for (int i = 0; i < cacheOptions.size(); i++) {
        DialogueOption& opt = cacheOptions[i];
        cout << "Option ID: " << opt.ID << endl;
        cout << "Option Leads To: " << opt.leadsTo << endl;
        cout << "Option Text: " << opt.text << endl;

        cout << "\nDialogue for this option:\n" << endl;
        for (int x = 0; x < opt.dialogue.size(); x ++) {
            cout << opt.dialogue[x].character->name << ": " << opt.dialogue[x].subtitles << endl;
        }
    }
    cout << endl;

    return 0;
}
