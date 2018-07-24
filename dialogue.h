#pragma once

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

    int ID;
    int leadsTo; // ID of the dialogueScreen this option leads to

    std::string text; // the actual text to show for the option
    std::vector<DialogueClass> dialogue; // the dialogue between characters for this option

};


// this holds data for the entire dialogue screen, all the different dialogue options
class DialogueScreen {
public:

    DialogueScreen() : ID(0)
    {

    }

    DialogueScreen(int id, std::vector<DialogueOption> opt)
        : ID(id), options(opt)
    {

    }

    int ID;

    std::vector<DialogueOption> options; // all the options for this screen

};


// a master class which holds all this data together
// can be instantiated based on characters, etc, as necessary
class DialogueTree {
public:



};
