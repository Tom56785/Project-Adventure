#ifndef TAROT_INVENTORY
#define TAROT_INVENTORY

#include <string>
#include <vector>


// shouldn't be invoked directly unless for insertion into inventory class
class Item {
private:

    Item(); // <-- PRIVATE constructor
            // this means that this constructor MUST be called using the parametized constructor

    // having these private is important so that these can only be edited by internal functions and not directly
    // better for handling moments where there may be a quantity reduction meaning the player no longer has that item

    int _ID;
    std::string _name;
    std::string _desc;

    void* _glyph; // PLACEHOLDER

public:

    int quantity;
    bool persistent; // <-- can be changed to true to permanently keep in inventory despite negative quantity

    Item(int ID, int quant, std::string name, std::string desc, bool pers = false)
        : _ID(ID), quantity(quant), _name(name), _desc(desc), persistent(pers)
        // ^^^ Initialising list, vvv extra code for initialisation
    {

    }

    // retrieves the ID of the item, used for searching
    int id() {
        return _ID;
    }

    // retrieves the name of the item
    std::string name() {
        return _name;
    }

    // retrieves the description of the item
    std::string desc() {
        return _desc;
    }

    // PLACEHOLDER, retrives the glyph/texture of the item
    void* glyph() {
        return _glyph;
    }


};

Item null(0, 0, "NULL", "NULL");

class Inventory {
public:

    // invoked directly to access items you would need to go through steps
    // inventory.items[ID].quantity;
    // ^^^ this is not desirable
    // vvv IDEAL
    // inventory[ID].quantity;
    // ^^^ using operator overloads as a solution

    // default constructor
    Inventory() {

    }

    // OPTIONAL constructor class for creating items from a vector of items
    Inventory(std::vector<Item> inv)
        : _items(inv)
    {

    }

    // add an item from a pre-made item
    void add_item(Item it) {
        _items.push_back(it);
    }

    // add an item from parameters
    void add_item(int ID, int quant, std::string name, std::string desc, bool pers = false) {
        _items.push_back(Item(ID, quant, name, desc, pers));
    }

    // remove an item with it's ID
    void remove_item(int ID) {
        if (!_items.size()) {
            // there are no items in the vector, do nothing
            return;
        }
        // loop through all the items and check each ID
        for (int i = 0; i < _items.size(); i++) {
            if (_items[i].id() == ID) {
                // the item was found in the inventory
                _items.erase(_items.begin() + i);
                return;
            }
        }
        // the item wasn't found, do nothing
        return;
    }

    // this function checks all items in the inventory and removes ones without any quantity
    // doesn't remove items that are 'persistent'
    void update() {
        if (!_items.size()) {
            // there are no items in the vector, do nothing
            return;
        }
        // loop through every item and check each one's persistency
        for (int i = 0; i < _items.size(); i++) {
            if (_items[i].quantity <= 0 && !_items[i].persistent) {
                // quantity is less than or equal to 0 and isn't persistent, remove it
                _items.erase(_items.begin() + i);
            }
        }
        return;
    }

    // returns a reference to the item using the item's ID
    // needs to be a reference otherwise any changes won't stick
    Item& operator[](int ID) {
        // search for the item in the vector with the ID
        if (!_items.size()) {
            // there are no items in the vector
            // return a NULL item
            return null;
        }
        // loop through all the items and check each ID
        for (int i = 0; i < _items.size(); i++) {
            if (_items[i].id() == ID) {
                // the item was found in the inventory
                // return the item
                return _items[i];
            }
        }
        // ELSE, return null
        return null;
    }


private:

    // vvv PRIVATE so that it can't be invoked directly
    // this ensures proper function for ID searching
    std::vector<Item> _items;

};

#endif


/*

Data required for inventory:

-Container for inventory items
-Retrieve an item from inventory
-Remove or edit quantities
-Search based on ID



Item class:
-ID
-Name
-Description
-Quantity
-Glyph/texture



*/
