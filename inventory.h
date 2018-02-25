#pragma once

#include "main.h"


// shouldn't be invoked directly unless for insertion into inventory class
class item {
private:

    item(); // <-- PRIVATE constructor
            // this means that this constructor MUST be called using the parametized constructor

    // having these private is important so that these can only be edited by internal functions and not directly
    // better for handling moments where there may be a quantity reduction meaning the player no longer has that item

    int _ID;
    std::string _name;
    std::string _desc;

    void* _glyph; // PLACEHOLDER


    class quantity_class {
    private:

        int _quantity;

    public:


        // using operator overloads to set and retrieve data

        // retrieves quantity of the item
        // item.quantity();
        int operator()() {
            return _quantity;
        }

        // sets a new quantity for the item
        // item.quantity = 99;
        quantity_class& operator=(int quant) {
            _quantity = quant;
        }

        // comparison operator, not necessary but useful
        // item.quantity == 36;
        bool operator==(int quant) {
            return (_quantity == quant);
        }

        // increments quantity by designated amount
        // item.quantity += 12;
        quantity_class& operator+=(int quant) {
            _quantity += quant;
        }

        // decrements quantity by designated amount
        // item.quantity -= 12;
        quantity_class& operator-=(int quant) {
            _quantity -= quant;
        }

        // multiplies quantity by designated amount
        // item.quantity *= 2;
        quantity_class& operator*=(int quant) {
            _quantity *= quant;
        }

        // divides quantity by designated amount
        // item.quantity /= 3;
        quantity_class& operator/=(int quant) {
            _quantity /= quant;
        }

    };

public:

    quantity_class quantity;
    bool persistent; // <-- can be changed to true to permanently keep in inventory despite negative quantity

    item(int ID, int quant, std::string name, std::string desc, bool pers = false)
        : _ID(ID), _name(name), _desc(desc)
        // ^^^ Initialising list, vvv extra code for initialisation
    {
        quantity = quant;
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

item null(0, 0, "NULL", "NULL");

class inv {
public:

    // invoked directly to access items you would need to go through steps
    // inventory.items[ID].quantity();
    // ^^^ this is not desirable
    // vvv IDEAL
    // inventory[ID].quantity();
    // ^^^ using operator overloads as a solution

    // default constructor
    inv() {

    }

    // OPTIONAL constructor class for creating items from a vector of items
    inv(std::vector<item> inventory)
        : _items(inventory)
    {

    }

    // add an item from a pre-made item
    void add_item(item it) {
        _items.push_back(it);
    }

    // add an item from parameters
    void add_item(int ID, int quant, std::string name, std::string desc, bool pers = false) {
        _items.push_back(item(ID, quant, name, desc, pers));
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
            if (_items[i].quantity() <= 0 && !_items[i].persistent) {
                // quantity is less than or equal to 0 and isn't persistent, remove it
                _items.erase(_items.begin() + i);
            }
        }
        return;
    }

    // returns a reference to the item using the item's ID
    // needs to be a reference otherwise any changes won't stick
    item& operator[](int ID) {
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
    std::vector<item> _items;

};


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
