#pragma once

#include "main.h"

using std::string;


// contains individual dialogue, the text to display and the character whom says it
class DialogueClass {
public:

    int ID;

    /// TO DO ///
    void* character; // the character which says this line, also contains colour data for the text
    /// TO DO ///

    string subtitles; // the text/subtitles for the dialogue to show on screen

    int time; // the amount of time to show this dialogue

};

// this is a single dialogue option, contains all its data and where it leads to
class DialogueOption {
public:

    int ID;
    int leadsTo; // ID of the dialogueScreen this option leads to

    string text; // the actual text to show for the option
    std::vector<DialogueClass> dialogue; // the dialogue between characters for this option

};


// this holds data for the entire dialogue screen, all the different dialogue options
class DialogueScreen {
public:

    int ID;

    std::vector<DialogueOption> options; // all the options for this screen

};


// a master class which holds all this data together
// can be instantiated based on characters, etc, as necessary
class DialogueTree {
public:



};
