#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "character.h"


// contains individual dialogue, the text to display and the character whom says it
class DialogueClass {
public:

    DialogueClass() : ID(0), time(0)
    {

    }

    DialogueClass(int id, Character* chr, std::string text, int t)
        : ID(id), character(chr), subtitles(text), time(t)
    {

    }

    int ID;

    // pointer to the original character rather than a direct copy
    Character* character; // the character which says this line, also contains colour data for the text

    std::string subtitles; // the text/subtitles for the dialogue to show on screen

    int time; // the amount of time to show this dialogue

};

// this is a single dialogue option, contains all its data and where it leads to
class DialogueOption {
public:

    DialogueOption() : ID(0), leadsTo(0)
    {

    }

    DialogueOption(int id, int lt, std::string txt, std::vector<DialogueClass> dial)
        : ID(id), leadsTo(lt), text(txt), dialogue(dial)
    {

    }

    DialogueOption(int id, int lt, std::string txt)
        : ID(id), leadsTo(lt), text(txt)
    {

    }

    int ID;
    int leadsTo; // ID of the dialogueScreen this option leads to

    std::string text; // the actual text to show for the option
    std::vector<DialogueClass> dialogue; // the dialogue between characters for this option

};


// this holds data for the entire dialogue screen, all the different dialogue options
class DialogueScreen {
public:

    DialogueScreen() : ID(0), passive(false)
    {

    }

    DialogueScreen(int id, bool p, std::vector<DialogueOption> opt)
        : ID(id), passive(p), options(opt)
    {

    }

    int ID;
    bool passive;
    // if this option is passive then options aren't shown and goes straight to dialogue
    // this is useful for when there is dialogue when starting a conversation with a character

    std::vector<DialogueOption> options; // all the options for this screen

};


// a master class which holds all this data together
// can be instantiated based on characters, etc, as necessary
class DialogueTree {
public:

    DialogueTree() : ID(0), root(0)
    {

    }

    DialogueTree(int id, int r, std::vector<DialogueScreen> scr)
     : ID(id), root(r), screens(scr)
    {

    }

    int ID;
    int root; // which screen to start at when running the dialogue, CAN be altered

    std::vector<DialogueScreen> screens; // all of the dialogue screens for this tree


    // this function finds the index of the screen based on its ID
    int findScreen(int id) {
        // loop through all the screens until the correct one is found
        for (int i = 0; i < screens.size(); i++) {
            if (screens[i].ID == id) {
                // the correct screen has been found
                // return the index
                return i;
            }
        }
        return 0;
    }

    // this function retrieves input for a choice
    int getInput() {
        // WILL BE UPDATED TO TAKE INPUT FROM MOUSE/KEYBOARD, ETC, LATER ON

        std::cout << "\nChoice: ";

        int inp;
        std::cin >> inp;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(99999, '\n');
            return 1;
        }
        std::cin.ignore(99999, '\n');

        return inp;
    }

    // function to output dialogue for given option, easy for reuse
    void outputDialogue(DialogueOption& option) {
        for (int i = 0; i < option.dialogue.size(); i++) {
            std::cout << option.dialogue[i].character->name << ": " << option.dialogue[i].subtitles << std:: endl;
        }
    }


    // function to invoke the dialogue and run it
    // can return a number based on what happens in the dialogue
    int run() {

        int start = root; // starting position

        do {
            // firstly check if the screen is passive
            // if so then just output the dialogue
            if (screens[start].passive) {
                for (int i = 0; i < screens[start].options[0].dialogue.size(); i++) {
                    std::cout << screens[start].options[0].dialogue[i].character->name << ": " << screens[root].options[0].dialogue[i].subtitles << std:: endl;
                }
                start = findScreen(screens[start].options[0].leadsTo);
            } else {

                // output the starting positions' options
                for (int i = 0; i < screens[start].options.size(); i++) {
                    std::cout << (i + 1) << ". " << screens[start].options[i].text << std::endl;
                }

                // retrieve input and select an option
                // WILL BE UPDATED TO TAKE INPUT FROM MOUSE/KEYBOARD, ETC, LATER ON

                int choice = getInput();

                // output the dialogue for this option
                outputDialogue(screens[start].options[choice - 1]);

                // adjust the new starting position
                start = findScreen(screens[start].options[choice - 1].leadsTo);

            }

            std::cout << std::endl;

        } while (start != 0);
        // when the start is set to 0, that means exit the dialogue

    }

};
